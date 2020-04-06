var http = require("http")
var nodedump = require("nodedump");
var leekList = [];
var leek = function()
{
  leekList.push("leek  "+ Math.random());
}
http.createServer(function(req,res){
   leek();
   res.writeHead(200,{'Content-Type':"text/plain"});
   res.end('Hello world');
}).listen(12345);
console.log('server on 12345');