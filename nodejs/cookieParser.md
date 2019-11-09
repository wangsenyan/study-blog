### cookie设置
### cookie获取

### cookie签名
### cookie解析

```js
const express =require("express");
const cookieParser = require("cookie-parser");
const app = express();

app.use(cookieParser("secert"));
//相当于
app.use(function(req,res,next){
  req.cookies = cookie.parse(req.headers.cookie);
})

var cookieParser = function(secret){
  return function(req,res,next){
    req.secret = secret;
    //...
    next();
  }
}

//设置cookie
req.cookie = function(name,value,options){
  let secret =  this.req.secret;
  let signed = options.signed;
 
  if(signed){
    val = 's:'+sign(val,secret);
  }
  this.append('Set-Cookie',cookie.serialize(name,String(val),options));
  return this;
}

res.cookie("name","value",{signed:true});
res.end('ok');
//获取cookie
req.cookies
req.singedCookies
//签名函数
function sign(val,secret){
  //return val + '.' + hmac(val,secret);
    return val + '.' + crypto
    .createHmac('sha256', secret)
    .update(val)
    .digest('base64')
    .replace(/\=+$/, '');
}

//签名cookie解析
//1.将签名cookie对应的原始值提取出来
//2.验证签名cookie是否合法

function signedCookie(str,secret)
{
   if(str.substr(0,2)!='s:')
     return str;
    
   var val = unsign(str.slice(2),secret);
   if(val!=false)
     return val;
   return false;
}

function unsign(val,secret)
{
  var str=val.slice(0,val.lastIndexOf('.')),mac=exports.sign(str,secret);
  return sha1(mac)==sha1(val)?str:false;//感觉不对
}
```