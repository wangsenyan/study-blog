module.exports = function execute(app, instructions, callback) {
  callback = callback || function() {};

  app.booting = true;

  patchAppLoopback(app);
  assertLoopBackVersion(app);

  setEnv(app, instructions);
  setHost(app, instructions);
  setPort(app, instructions);
  setApiRoot(app, instructions);//config.restApiRoot 
  applyAppConfig(app, instructions);//将config写入setting

  setupDataSources(app, instructions);
  setupModels(app, instructions);
  setupMiddleware(app, instructions);
  setupComponents(app, instructions);

  // Run the boot scripts in series synchronously or asynchronously
  // Please note async supports both styles
  async.series([
    function(done) {
      runBootScripts(app, instructions, done);
    },
    function(done) {
      enableAnonymousSwagger(app, instructions);
      done();
    },
    // Ensure both the "booted" event and the callback are always called
    // in the next tick of the even loop.
    // See http://blog.izs.me/post/59142742143/designing-apis-for-asynchrony
    process.nextTick,
  ], function(err) {
    app.booting = false;

    if (err) return callback(err);

    app.emit('booted');

    callback();
  });
};

function setupDataSources(app, instructions) {
  forEachKeyedObject(instructions.dataSources, function (key, obj) {
    var opts = {
      useEnvVars: true,
    };
    obj = getUpdatedConfigObject(app, obj, opts);
    var lazyConnect = process.env.LB_LAZYCONNECT_DATASOURCES;
    if (lazyConnect) {
      obj.lazyConnect =
        lazyConnect === 'false' || lazyConnect === '0' ? false : true;
    }
    app.dataSource(key, obj);
  });
}

//loopback/lib/application.js
app.dataSource = function(name, config) {
  try {
    var ds = dataSourcesFromConfig(name, config, this.connectors, this.registry);
    this.dataSources[name] =
    this.dataSources[classify(name)] =
    this.dataSources[camelize(name)] = ds;
    ds.app = this;
    return ds;
  } catch (err) {
    if (err.message) {
      err.message = g.f('Cannot create data source %s: %s',
        JSON.stringify(name), err.message);
    }
    throw err;
  }
};

function dataSourcesFromConfig(name, config, connectorRegistry, registry) {
  var connectorPath;

  assert(typeof config === 'object',
    'can not create data source without config object');

  if (typeof config.connector === 'string') {
    const connectorName = config.connector;
    if (connectorRegistry[connectorName]) {
      config.connector = connectorRegistry[connectorName];
    } else {
      connectorPath = path.join(__dirname, 'connectors', connectorName + '.js');

      if (fs.existsSync(connectorPath)) {
        config.connector = require(connectorPath);
      }
    }
    if (config.connector && typeof config.connector === 'object' && !config.connector.name)
      config.connector.name = connectorName;
  }

  return registry.createDataSource(name, config);
}

//loopback/lib/registry.js
//通过将提供的选项传递到连接器来创建数据源 什么是连接器
Registry.prototype.createDataSource = function (name, options) {
  var self = this;

  var ds = new DataSource(name, options, self.modelBuilder);//连接数据库
  ds.createModel = function (name, properties, settings) {
    settings = settings || {};
    var BaseModel = settings.base || settings.super;
    if (!BaseModel) {
      // Check the connector types
      var connectorTypes = ds.getTypes();
      if (Array.isArray(connectorTypes) && connectorTypes.indexOf('db') !== -1) {
        // Only set up the base model to PersistedModel if the connector is DB
        BaseModel = self.PersistedModel;
      } else {
        BaseModel = self.Model;
      }
      settings.base = BaseModel;
    }
    var ModelCtor = self.createModel(name, properties, settings);
    ModelCtor.attachTo(ds);
    return ModelCtor;
  };

  if (ds.settings && ds.settings.defaultForType) {
    var msg = g.f('{{DataSource}} option {{"defaultForType"}} is no longer supported');
    throw new Error(msg);
  }

  return ds;
};