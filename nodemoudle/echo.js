/*var net = require('net');
var server = net.createServer(function(socket){
    socket.on('data',function(data){
        socket.write(data);
    });
});
server.listen(8888)
*/
/*var EventEmitter = require('events').EventEmitter;
var channel = new EventEmitter();
var net = require('net');
channel.clients = {};
channel.subscriptions = {};
channel.on('join',function(id,client){
    this.clients[id]=client;
    this.subscriptions[id]=function(senderId,message){
        if(id!=senderId){
        this.clients[id].write(message);
        }
    }
    this.on('broadcast',this.subscriptions[id]);
});
var server = net.createServer(function(client){
    var id=client.remoteAddress+':'+client.remotePort;
    client.on('connect',function(){
        channel.emit('join',id,client);
    });
    client.on('data',function(data){
        data = data.toString();
        channel.emit('broadcast',id,data);
    })
})
server.listen(8888)
*/
//匿名函数保留全局变量的值
/*function asyncFunction(callback){
    setInterval(callback,2000);
}
var color = 'blue';
(function(color){
    asyncFunction(function(){
        console.log('the color is '+color);
    })
})(color);
color = 'green'
*/
/**
 * 数据流Stream
 */
/**var http = require('http');
var parse = require('url').parse;
var join = require('path').join;
var fs = require('fs');

var root = __dirname;
var server = http.createServer(function(req,res){
    var url = parse(req.url);
    var path = join(root,url.pathname);
    fs.stat(path,function(err,stat){
        if(err){
            if('ENOENT'==err.code){
                res.statusCode = 404;
                res.end('Not Found');
            }else{
                res.statusCode = 500;
                res.end('Internal Server Error');
            }
        }else{
            res.setHeader('Content-length',stat.size);
            var stream = fs.createReadStream(path);
            stream.pipe(res);
            stream.on('error',function(err){
                res.statusCode = 500;
                res.end('Internal Server Error')
            });
            stream.on('end',function(){
               res.end();
            });
        }
    })
    //readStream.on('data',function(chunk){
      //  res.write(chunk);
    //})
});
server.listen(3000);
*/
var http = require('http');
var querystring = require('querystring');
var formidable=require('formidable');
var items=[];

var server = http.createServer(function(req,res){
    if('/'==req.url){
        switch(req.method){
            case 'GET':
               show(res);
               break;
            case 'POST':
               add(req,res);
               break;
            default:
               badRequest(res);
        }
    }else{
        notFound(res);
    }
});
server.listen(3000);
function show(res){
    var html='<html><head><title>Todo List</title></head></body>'
            +'<h1>Todo List</h1>'
            +'<ul>'
            +items.map(function(item){
                return '<li>'+item+'</li>'
            }).join('')
            +'</ul>'
            +'<form method="post" action="/">'
            +'<p><input type="text" name="name"/></p>'
            +'<p><input type="file" name="file"/></p>'
            +'<p><input type="submit" value="Upload"/></p>'
            +'</form></body></html>';
    res.setHeader('Content-Type','text/html');
    res.setHeader('Content-length',Buffer.byteLength(html));
    res.end(html);
}
function notFound(res){
    res.statusCode = 404;
    res.setHeader('Content-Type','text/plain');
    res.end('Not Found');
}
function badRequest(res){
    res.statusCode = 400;
    res.setHeader('Content-Type','text/plain');
    res.end('Bad Request');
}
function add(req,res){
    var body='';
    req.setEncoding('utf8');
    req.on('data',function(chunk){body+=chunk});
    req.on('end',function(){
        var obj = querystring.parse(body);
        items.push(obj.item);
        show(res);
    });
}
function upload(req,res){
   if(!isFormData(req)){
    res.statusCode = 400;
    res.end('Bad Request:expecting multipart/form-data');
    return;
   }
   var form = new formidable.IncomingForm();
   form.parse(req);
}
function isFormData(req){
    var type = req.headers['content-type']||'';
    return 0 == type.indexOf('multipart/form-data');
}