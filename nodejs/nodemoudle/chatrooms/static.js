var connect = require('connect');
var static = require('serve-static')
var app = connect();
app.use(connect.directory(__dirname+'/public/javascripts'))
app.use(static(__dirname+'/public/javascripts'))
app.use('/queen',static(__dirname+'/public/javascripts'))
app.listen(3000)
//static('public') ==process.cwd()+'public'