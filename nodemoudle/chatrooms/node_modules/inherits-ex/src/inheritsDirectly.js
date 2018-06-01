var newPrototype = require('./newPrototype');
var setPrototypeOf = require('./setPrototypeOf');
var defineProperty = require('./defineProperty');

//just replace the ctor.super to superCtor,
module.exports = function(ctor, superCtor) {
  defineProperty(ctor, 'super_', superCtor);
  defineProperty(ctor, '__super__', superCtor.prototype);//for coffeeScirpt super keyword.
  ctor.prototype = newPrototype(superCtor, ctor);
  setPrototypeOf(ctor, superCtor);//additional static inheritance
};
