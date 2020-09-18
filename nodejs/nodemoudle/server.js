var http = require("http")
var memwatch = require("memwatch");
memwatch.on('leak', function (info) {
    console.log('leak');
    console.log(info);
})
memwatch.on('stats', function (stats) {
    console.log("stats");
    console.log(stats);
})
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
console.log('server on 8080');