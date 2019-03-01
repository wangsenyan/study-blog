//basicAuth()
//csff()
//errorHandler()
/*var app=connect()
        .use(connect.basicAuth('tj','tobi')) //user+password
var users={
    tobi:'foo',
    loki:'bar',
    jane:'baz'
}
var app = connect()
          .use(connect.basicAuth(function(user,pass){
            return users[user] ===pass;
          }))
var app = connect();
    app.use(connect.basicAuth(function(user,pass,callback){
        User.authenticate({user:user,pass:pass},getUser);
        function getUser(err,user){
            if(err)return callback;
            callback(null,user);
        }
    }))
*/
var connect = require('connect');
var basicAuth = require('basic-auth')
var errorhandler = require('errorhandler')
var app = connect()
          .use(basicAuth({'tobi':'ferret'}))
          .use(function(req,res,next){
            setTimeout(function(){
                next(new Error('something broke!'))
            },500)
          })
          .use(errorhandler());
app.listen(3000)