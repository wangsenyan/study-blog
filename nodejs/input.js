var http = require('http')
var querystring = require('querystring')

var postData = querystring.stringify({
	'content':'老师真帅！',
	'cid':8837
})
var options = {
	hostname: 'www.imooc.com',//可以成功？
	port:80,
	path:'/course/docomment',
	method:'POST',
	headers:{
'Accept':'application/json, text/javascript, */*; q=0.01',
'Accept-Encoding':'gzip, deflate',
'Accept-Language':'zh-CN,zh;q=0.8',
'Connection':'keep-alive',
'Content-Length':postData.length,
'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
'Cookie':'imooc_uuid=cc8f7062-6e6f-40db-a97f-ace6c9aa9241; imooc_isnew_ct=1500520184; loginstate=1; apsid=A4ZTY1M2NmYTk1NDE4M2M2ZjQzZDRhYTk2MmQwZWIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMzgzNDI5MAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAyNjMzNjAwNzAyQHFxLmNvbQAAAAAAAAAAAAAAAAAAADExZTJlZTM1OWM1ZjllZWJkYTczNDI0NDVlZTFkYjFjSh9wWUofcFk%3DMT; last_login_username=2633600702%40qq.com; PHPSESSID=nh23ungfaia435o3vr75kjgri1; IMCDNS=0; Hm_lvt_f0cfcccd7b1393990c78efdeebff3968=1500520189,1500802989; Hm_lpvt_f0cfcccd7b1393990c78efdeebff3968=1500803481; imooc_isnew=2; cvde=59746fabd8f7d-44',
'Host':'www.imooc.com',
'Origin':'http://www.imooc.com',
'Referer':'http://www.imooc.com/video/8837',
'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36',
'X-Requested-With':'XMLHttpRequest'
	}
}


var req = http.request(options,function(res){
	console.log('Status' + res.statusCode)
	console.log('headers:' + JSON.stringify(res.headers))
	res.on('data',function(chunk){
		console.log(Buffer.isBuffer(chunk))
		console.log(typeof chunk)
	})
	res.on('end',function(){
		console.log('Over！')
	})
})
req.on('error',function(e){
	console.log('Error:' + e.message)
})
req.write(postData)
req.end()