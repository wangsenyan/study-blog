const http require('http');
http.Agent(){
    new Agent([options])
    agent.createConnection(options[,callback])
    agent.keepSocketAlive(socket)
    agent.reuseSocketAlice(socket)
    agent.destroy()
    agent.freeSockets
    agent.getName(options)
    agent.maxFreeSockets
    agent.requests
    agent.socket
}
http.clientRequest(){
    'abort'
    'connect'
    'continue'
    'response'
    'socket'
    'Event:'timeout''
    'upgrade'
    request.abort()
    request.aborted
    request.createConnection
    request.end([data[,encoding]][,callback])
    request.flushHeaders()
    request.getHeader(name,value)
    request.setNoDelay([noDelay])
    request.setSocketKeepAlive([enable][,initialDelay])
    request.setTimeout(timeout[,callback])
    request.socket
    request.write(chunk[,encoding][,callback])
}
http.Server(){
    'checkContinue'
    'checkExpectation'
    'clientError'
    'close'
    'connect'
    'connection'
    'request'
    'upgrade'
    server.listen()
    server.listening
    server.maxHeadersCount
    server.setTimeout([msecs][,callback])
    server.setTimeout
    server.keepAliveTimeout
}
http.ServerResponse(){
    'close'
    'finish'
    response.addTrailers(headers)
    response.connection
    response.end([data][,encoding][,callback])
    response.finished
    response.getHeader(name)
    response.getHeaderNames()
    response.getHeaders()
    response.hasHeader(name)
    response.headersSent
    response.removeHeader(name)
    response.sendDate
    response.setHeader(name,value)
    response.setTimeout(msecs[,callback])
    response.socket
    response.statusCode
    response.statusMessage
    response.write(chunk[,encoding][,callback])
    response.writeContinue()
    response.writeHead(statusCode[,statusMessage][,headers])
}
http.incomingMessage(){
    'aborted'
    'colse'
    message.destroy([error])
    message.headers
    message.httpVersion
    message.method
    message.rawHeaders
    message.rawTrailers
    message.setTimeout(msecs, callback)
    message.socket
    message.statusCode
    message.statusMessage
    message.trailers
    message.url
}
http.MTTHODS
http.STATUS_CODES
http.createServer([requestListener])
http.get(options[,callback])
http.globalAgent
http.request(options[,callback])

//一个node HTTP服务器实际就是一个事件发射器，一个可继承、能够添加事件发射机处理能力的类
//继承自EventEmitter
//http.createServer(function(req,res))
//req.method=='POST'||'GET'||'PUT'||'DELETE'
//req.setEncoding('utf8') 默认是buffer
//req.setHeader('Content-Length',Buffer.byteLength(body))
//读取一个文件(ReadableStream)并把其中的内容写到另外一个文件中(writeableStream)用的就是管道
```
var readStream = fs.createReadStream('文件1');
var writeStream = fs.createWriteStream('文件2');
readStream.pipe(writeStream);
所有ReadalbeStream都能接入任何一个WritableStream，比如http请求(req)对象就是ReadableStream
req.pipe(fs.createWriteStream('file'))
```
//<form method="post" action='/'>
