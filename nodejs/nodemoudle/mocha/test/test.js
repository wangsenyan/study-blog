var lib = require('../index');
var fs = require('fs')
describe('module',function(){
    describe('limit',function(){
        it('limit shoud success',function(){
            lib.limit(10);
        })
    })
})
describe('async',function(){
    it('async',function(done){
        lib.async(function(result){
            done();
        });
    });
});
// describe('getContent',function(){
//     var _readFile;
//     before(function(){
//         _readFile = fs.readFile;
//         fs.readFile = function(filename,encoding,callback){
//             process.nextTick(function(){
//                 callback(new Error('mocha readFile error'));
//             });
//         };
//     });
//     it('what is it?',function(){
//         lib.getContent('./test.js','utf8',function(err,data){
//            if(err) console.log(err)
//             console.log(data)
//         })
//     })
//     after(function(){
//         fs.readFile = _readFile;
//     })
// })
it('limit shoud return success',function(){
    var lib = rewire('../index');
    var limitit = lib._get_('_adding')
    limitit(10,10);
})