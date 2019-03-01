var connect = require('connect')
var favicon = require('serve-favicon')
var cookieParser = require('cookie-parser')
var session = require('express-session')
var RedisStore = require('connect-redis')(session)//important
//var session = require('')
var sessionOpts = {
    key:'wangsenyan',
    cookie:{maxAge:3600000*24,secure:true}
}
var app = connect()
          .use(favicon(__dirname+'/favicon.ico'))
          .use(cookieParser('wangsenyan'))
          .use(session({store:new RedisStore({prefix:'sid'})}))
          .use(function(req,res,next){
            res.setHeader('Content-Type','text/html')
            res.write(`<p>views: ${req.session.views} </p>
                       <p>expires in: ${req.session.cookie.maxAge/1000} </p>
                       <p>path: ${req.session.path} </p>
                       <p>httpOnly: ${req.session.httpOnly} </p>
                       <p>domain: ${req.session.domain} </p>
                       <p>secure: ${req.session.secure} </p>
                      `)
          })
          .listen(3000)
/**
 * domaim 域名
 * path 路径
 * secure 安全连接
 * httpOnly 防止客户端脚本访问cookie数据
 * maxAge
 * 
 *
 */