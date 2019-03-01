var connect = require('connect');
var logger = require('morgan');
var methodOverride = require('method-override');
var bodyParser = require('body-parser')
function edit(req,res,next){
    if('GET'!=req.method)return next();
    res.setHeader('Content-Type','text/html');
    res.write('<form method="post" enctype="application/x-www-form-urlencoded">');
    res.write('<input type="hidden" name="_method" value="PUT"/>');
    res.write('<input type="text" name="user[name]" value="Tobi"/>');
    res.write('<input type="submit" value="Updata"/>');
    res.write('</form>');
    res.end();
}
function update(req,res,next){
    if('PUT'!=req.method)return next();
    res.end('Updated name to '+ req.body.user.name);
}
var app= connect()
         .use(logger('dev'))
         .use(bodyParser())
         .use(methodOverride(function(req,res){
            if(req.body&&typeof req.body ==='object'&&'_method' in req.body){
                var method = req.body._method
                delete req.body._method
                return method
            }
         }))
         .use(edit)
         .use(update)
         .listen(3000)