var connect = require('connect');
var express = require('express')
var app = express();
var request = require('superagent');
var apikey ="f607aace16ec412e8913cabf133f0af4";
var secret_key = "8CC90277703A4A59";
var url = 'https://www.testin.cn/account/login.htm';
var params = {
      apikey: apikey,
      mkey: "proxyapi",
      action: "user",
      op: "AppUser.login",
      timestamp: (new Date()).getTime(),
      data: { thirdUniqueid: 'apicloud' }
}
app.use(function(req,res,next){
    return 
})
   .use(function(req,res,next){
     console.log(res)
   }).listen(3000)
function Post (url, params) {
  return new Promise((resolve,reject)=>{
    request.post(url)
    .send(params)
    .set('Accept', 'application/json')
    .end(function (err,res){
        if(err)return reject(err)
        return resolve(res)
    })
  })
}
app.get('/',async function(req,res){
    let data = await Post(url,params);
    console.log(data)
})
