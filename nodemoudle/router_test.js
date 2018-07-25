var parse = require('url').parse;
module.exports = function route(obj){
    return function(req,res,next){
        if(!obj[req.method]){
            next();
            return;
        }
        var routes = obj[req.method] //obj中符合req.method的项
        var url = parse(req.url)
        var paths=Object.keys(routes)
        for(var i=0;i<paths.length;i++){
            var path = paths[i];
            var fn = routes[path];
            path=path
                 .replace(/\//g,'\\/')
                 .replace(/:(\w+)/g,'([^\\/]+)');
            var re = new RegExp('^'+path+'$');
                     var captures = url.pathname.match(re)
                     if(captures){
                        var args = [req,res].concat(captures.slice(1));
                        fn.apply(null,args);
                        return;
                     }
        }
        next();
    }
}

  var routers = {
    "follow":{
       "/del":"post",
       "/add":"post",
       "/list":"get",
    },
    "test":{
      "/delete":"delete",
      "/post":"post",
      "/head":"head",
      "/options":"options",
      "/patch":"patch",
      "/put":"put"
    }
  }
  for(var  i in routers){
    var actions = routers[i];
    for(var j in actions){
       //j == "/login" ...
       var path ="/api/"+i+j;
       var method = actions[j];
       (function(path,method){
          app[method](path ,function(req,res){
             var body = req.body
             var options = getOptions(method,path,body);
             request(options,function(e,r,b){
               if(e){
                 console.log('this is err',e)
                 return res.err(e);
               }else{ 
                 console.log(options)
                 return res.ok(r);
               }
             })
          })
       })(path,method)
    }
  }