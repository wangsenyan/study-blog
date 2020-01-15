//初始化app
exports = module.exports = function bootLoopBackApp(app, options, callback) {
  // backwards compatibility with loopback's app.boot
  options.env = options.env || app.get('env');

  var instructions = compile(options);//获取所有配置
  execute(app, instructions, callback);
};
