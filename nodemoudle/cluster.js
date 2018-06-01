const cluster = require('cluster');
const http = require('http');
const numCPUs = require('os').cpus().length;

//console.log(numCPUs) 4
//process.pid 进程id
if(cluster.isMaster){
    debugger;
    console.log(`主进程 ${process.pid} 正在运行`);
    for(let i =0;i<numCPUs;i++){
        cluster.fork();
    }
    cluster.on('exit',(worker,code,signal)=>{
        console.log(`工作进程 ${worker.process.pid} 已退出`);
    })
}else{
    http.createServer((req,res)=>{
        res.setHeader('Content-Type','text/plain');
        res.writeHead(200);
        res.end('hello word\n');
    }).listen(3000);
    console.log(`工作进程 ${process.pid} 已启动`);
}