var request = require('superagent');
request.post('http://localhost:3000')
       .set('Cookie','foo=bar,bar=j:{"foo":"bar"}')
       .end(function(err,data){
        console.log(data)
       })