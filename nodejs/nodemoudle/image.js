var http = require('http');
var fs = require('fs');
http.createServer(function(req,res){
    res.writeHead(200,{'Content-Type':'video/qlv'});
    fs.createReadStream('./迈克尔·杰克逊：就是这样 蓝光(1080P).qlv').pipe(res);
}).listen(3000);
console.log('server runnng at http://localhost:3000');