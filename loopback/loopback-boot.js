/*
1.loadAppConfig
2.loadDataSources
3.loadModels
4.loadMiddleware
5.loadComponents
*/

function loadNamed(rootDir, env, name, mergeFn) {
  //根据rootDir,env,name获取配置文件
  var files = findConfigFiles(rootDir, env, name);
  if (files.length) {
    debug('found %s %s files', env, name);
    files.forEach(function(f) { debug('  %s', f); });
  }
  //加载文件并设置name为路径
  var configs = loadConfigFiles(files);
  var merged = mergeConfigurations(configs, mergeFn);

  debug('merged %s %s configuration %j', env, name, merged);

  return merged;
}

//可在server.js中设置 process.env.NODE_ENV 选择
function findConfigFiles(appRootDir, env, name) {
  var master = ifExists(name + '.json');
  if (!master && (ifExistsWithAnyExt(name + '.local') ||
    ifExistsWithAnyExt(name + '.' + env))) {
    g.warn('WARNING: Main {{config}} file "%s.json" is missing', name);
  }
  if (!master) return [];//必须有不带环境的配置文件

  var candidates = [
    master,
    ifExistsWithAnyExt(name + '.local'),
    ifExistsWithAnyExt(name + '.' + env),
  ];

  return candidates.filter(function(c) { return c !== undefined; });

  function ifExists(fileName) {
    var filepath = path.resolve(appRootDir, fileName);
    return utils.fileExistsSync(filepath) ? filepath : undefined;
  }

  function ifExistsWithAnyExt(fileName) {
    return ifExists(fileName + '.js') || ifExists(fileName + '.json');
  }
}

function loadConfigFiles(files) {
  return files.map(function (f) {
    var config = cloneDeep(require(f));
    Object.defineProperty(config, '_filename', {
      enumerable: false,
      value: f,
    });
    debug('loaded config file %s: %j', f, config);
    return config;
  });
}

//next compile.js