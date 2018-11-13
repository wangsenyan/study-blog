var cherrio=require('cherrio');
var http=require('http');
var iconv=require('iconv-lite');

var url='http://discuzt.cr180.com/discuzcode-db.html';
http.get(url,function(sres){
   var chunks=[];
   sres.on('data',function(chunk){
   	chunks.push(chunk);
   });
   sres.on('end',function(){
   	console.log(chunks);
   })
})