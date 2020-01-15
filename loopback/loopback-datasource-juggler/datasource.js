function DataSource(name, settings, modelBuilder) {
  if (!(this instanceof DataSource)) {
    return new DataSource(name, settings);
  }

  // Check if the settings object is passed as the first argument
  if (typeof name === 'object' && settings === undefined) {
    settings = name;
    name = undefined;
  }

  // Check if the first argument is a URL
  if (typeof name === 'string' && name.indexOf('://') !== -1) {
    name = utils.parseSettings(name);
  }

  // Check if the settings is in the form of URL string
  if (typeof settings === 'string' && settings.indexOf('://') !== -1) {
    settings = utils.parseSettings(settings);
  }

  this.modelBuilder = modelBuilder || new ModelBuilder();
  this.models = this.modelBuilder.models;
  this.definitions = this.modelBuilder.definitions;
  this.juggler = juggler;

  // operation metadata
  // Initialize it before calling setup as the connector might register operations
  this._operations = {};

  this.setup(name, settings);

  this._setupConnector();

  // connector
  const connector = this.connector;

  // DataAccessObject - connector defined or supply the default
  const dao = (connector && connector.DataAccessObject) || this.constructor.DataAccessObject;
  this.DataAccessObject = function() {
  };

  // define DataAccessObject methods
  Object.keys(dao).forEach(function(name) {
    const fn = dao[name];
    this.DataAccessObject[name] = fn;

    if (typeof fn === 'function') {
      this.defineOperation(name, {
        accepts: fn.accepts,
        'returns': fn.returns,
        http: fn.http,
        remoteEnabled: fn.shared ? true : false,
        scope: this.DataAccessObject,
        fnName: name,
      });
    }
  }.bind(this));

  // define DataAccessObject.prototype methods
  Object.keys(dao.prototype || []).forEach(function(name) {
    const fn = dao.prototype[name];
    this.DataAccessObject.prototype[name] = fn;
    if (typeof fn === 'function') {
      this.defineOperation(name, {
        prototype: true,
        accepts: fn.accepts,
        'returns': fn.returns,
        http: fn.http,
        remoteEnabled: fn.shared ? true : false,
        scope: this.DataAccessObject.prototype,
        fnName: name,
      });
    }
  }.bind(this));
}


//Set up the connector instance for backward compatibility with JugglingDB schema/adapter
DataSource.prototype._setupConnector = function() {
  this.connector = this.connector || this.adapter; // The legacy JugglingDB adapter will set up `adapter` property
  this.adapter = this.connector; // Keep the adapter as an alias to connector
  if (this.connector) {
    if (!this.connector.dataSource) {
      // Set up the dataSource if the connector doesn't do so
      this.connector.dataSource = this;
    }
    const dataSource = this;
    this.connector.log = function(query, start) {
      dataSource.log(query, start);
    };

    this.connector.logger = function(query) {
      const t1 = Date.now();
      const log = this.log;
      return function(q) {
        log(q || query, t1);
      };
    };
    // Configure the connector instance to mix in observer functions
    jutil.mixin(this.connector, OberserverMixin);
  }
};

// List possible connector module names
function connectorModuleNames(name) {
  const names = []; // Check the name as is
  if (!name.match(/^\//)) {
    names.push('./connectors/' + name); // Check built-in connectors
    if (name.indexOf('loopback-connector-') !== 0) {
      names.push('loopback-connector-' + name); // Try loopback-connector-<name>
    }
  }
  // Only try the short name if the connector is not from StrongLoop
  if (['mongodb', 'oracle', 'mysql', 'postgresql', 'mssql', 'rest', 'soap', 'db2', 'cloudant']
    .indexOf(name) === -1) {
    names.push(name);
  }
  return names;
}

/*!
 * Resolve a connector by name
 * @param name The connector name
 * @returns {*}
 * @private
 */
DataSource._resolveConnector = function(name, loader) {
  const names = connectorModuleNames(name);
  const connector = tryModules(names, loader);
  let error = null;
  if (!connector) {
    error = g.f('\nWARNING: {{LoopBack}} connector "%s" is not installed ' +
      'as any of the following modules:\n\n %s\n\nTo fix, run:\n\n    {{npm install %s --save}}\n',
    name, names.join('\n'), names[names.length - 1]);
  }
  return {
    connector: connector,
    error: error,
  };
};

//testable with DI
function tryModules(names, loader) {
  let mod;
  loader = loader || require;
  for (let m = 0; m < names.length; m++) {
    try {
      mod = loader(names[m]);
    } catch (e) {
      const notFound = e.code === 'MODULE_NOT_FOUND' &&
        e.message && e.message.indexOf(names[m]) > 0;

      if (notFound) {
        debug('Module %s not found, will try another candidate.', names[m]);
        continue;
      }

      debug('Cannot load connector %s: %s', names[m], e.stack || e);
      throw e;
    }
    if (mod) {
      break;
    }
  }
  return mod;
}


DataSource.prototype.setup = function(dsName, settings) {
  const dataSource = this;
  let connector;

  // First argument is an `object`
  if (dsName && typeof dsName === 'object') {
    if (settings === undefined) {
      // setup({name: 'myDataSource', connector: 'memory'})
      settings = dsName;
      dsName = undefined;
    } else {
      // setup(connector, {name: 'myDataSource', host: 'localhost'})
      connector = dsName;
      dsName = undefined;
    }
  }

  if (typeof dsName !== 'string') {
    dsName = undefined;
  }

  if (typeof settings === 'object') {
    if (settings.initialize) {
      // Settings is the resolved connector instance
      connector = settings;
      // Set settings to undefined to avoid confusion
      settings = undefined;
    } else if (settings.connector) {
      // Use `connector`
      connector = settings.connector;
    } else if (settings.adapter) {
      // `adapter` as alias for `connector`
      connector = settings.adapter;
    }
  }

  // just save everything we get
  this.settings = settings || {};

  this.settings.debug = this.settings.debug || debug.enabled;

  if (this.settings.debug) {
    debug('Settings: %j', this.settings);
  }

  if (typeof settings === 'object' && typeof settings.name === 'string' &&
      typeof dsName === 'string' && dsName !== settings.name) {
    // setup('myDataSource', {name: 'anotherDataSource', connector: 'memory'});
    // ds.name -> 'myDataSource' and a warning will be issued
    console.warn(
      'A datasource is created with name %j, which is different from the name in settings (%j). ' +
      'Please adjust your configuration to ensure these names match.',
      dsName, settings.name
    );
  }

  // Disconnected by default
  this.connected = false;
  this.connecting = false;
  this.initialized = false;

  this.name = dsName || (typeof this.settings.name === 'string' && this.settings.name);

  let connectorName;
  if (typeof connector === 'string') {
    // Connector needs to be resolved by name
    connectorName = connector;
    connector = undefined;
  } else if ((typeof connector === 'object') && connector) {
    connectorName = connector.name;
  } else {
    connectorName = dsName;
  }
  if (!this.name) {
    // Fall back to connector name
    this.name = connectorName;
  }

  if ((!connector) && connectorName) {
    // The connector has not been resolved
    const result = DataSource._resolveConnector(connectorName);
    connector = result.connector;
    if (!connector) {
      console.error(result.error);
      this.emit('error', new Error(result.error));
      return;
    }
  }

/**
 * Set up the data source. The following styles are supported:
 * ```js
 * ds.setup('myDataSource', {connector: 'memory'}); // ds.name -> 'myDataSource'
 * ds.setup('myDataSource', {name: 'myDataSource', connector: 'memory'}); // ds.name -> 'myDataSource'
 * ds.setup('myDataSource', {name: 'anotherDataSource', connector: 'memory'}); // ds.name -> 'myDataSource' and a warning will be issued
 * ds.setup({name: 'myDataSource', connector: 'memory'}); // ds.name -> 'myDataSource'
 * ds.setup({connector: 'memory'}); // ds.name -> 'memory'
 * ```
 * @param {String} dsName The name of the datasource. If not set, use
 * `settings.name`
 * @param {Object} settings The settings
 * @returns {*}
 * @private
 */
  if (connector) {
    const postInit = function postInit(err, result) {
      this._setupConnector();
      // we have an connector now?
      if (!this.connector) {
        throw new Error(g.f('Connector is not defined correctly: ' +
          'it should create `{{connector}}` member of dataSource'));
      }
      if (!err) {
        this.initialized = true;
        this.emit('initialized');
      }
      debug('Connector is initialized for dataSource %s', this.name);
      // If `result` is set to `false` explicitly, the connection will be
      // lazily established
      if (!this.settings.lazyConnect) {
        this.connected = (!err) && (result !== false); // Connected now
      }
      if (this.connected) {
        debug('DataSource %s is now connected to %s', this.name, this.connector.name);
        this.emit('connected');
      } else {
        // The connection fails, let's report it and hope it will be recovered in the next call
        if (err) {
          // Reset the connecting to `false`
          this.connecting = false;
          g.error('Connection fails: %s\nIt will be retried for the next request.', err);
          this.emit('error', err);
        } else {
          // Either lazyConnect or connector initialize() defers the connection
          debug('DataSource %s will be connected to connector %s', this.name,
            this.connector.name);
        }
      }
    }.bind(this);

    try {
      if ('function' === typeof connector.initialize) {
        // Call the async initialize method
        debug('Initializing connector %s', connector.name);
        connector.initialize(this, postInit);
      } else if ('function' === typeof connector) {
        // Use the connector constructor directly
        this.connector = new connector(this.settings);
        postInit();
      }
    } catch (err) {
      if (err.message) {
        err.message = 'Cannot initialize connector ' +
          JSON.stringify(connectorName) + ': ' +
          err.message;
      }
      throw err;
    }
  }
};