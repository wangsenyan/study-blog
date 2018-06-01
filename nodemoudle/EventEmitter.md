### 引入
Node.js 所有的异步I/O操作在完成时都会发送一个事件到事件队列
Node.js 里面的许多对象都会分发事件:一个net.Server对象会在每次有新连接时分发一个事件
events.EventEmitter的核心就是事件触发与事件监听功能的封装
```js
 EventEmitter = require('events').EventEmitter
```
### 实现监听
event.on('event',cb)实现对事件的监听
event.emit('event') 发射事件
emit()中的参数依次传入on的function()
```js
 var event = new EventEmitter()
 event.on('some_event',cb)
 event.emit('some_event');
```
or
```js
event.on('event',function(arg1,arg2){/*函数1*/})
event.on('event',function(arg1,arg2){/*函数2*/})
event.emit('event','arg1','arg2')
```
### EventEmitter实例的方法
 * addListener(event,listener) 为指定事件添加一个监听器到监听器数组的尾部
 * on(event,listener) 为事件注册一个监听器
 * once(event,listener) 为指定事件注册一个单次监听器
 * removeListener(event,listener) 移除某个指定事件的监听器，listener定义的回调函数，非匿名函数
 * removeAllListeners([event]) 移除所有的监听器[指定事件]
 * setMaxListeners(n) 设置监听器数量，默认为10个
 * listeners(event) 返回指定事件的监听器数组
 * emit(event,[arg1],[arg2],[...])
 ```js
 var event = require('events');
 var eventEmitter = new event.EventEmitter();

 var listener1 = function(){
   console.log('监听 listener1执行')
 }
  var listener2 = function(){
   console.log('监听 listener2执行')
 }

 eventEmitter.on('connection',listener1);
 eventEmitter.addListener('connection',listener2);
 
 var eventListeners = require('events').EventEmitter.listenerCount(eventEmitter,'connection');
 console.log(eventListeners+'个监听器监听事件链接');

 eventEmitter.emit('connection');

 eventEmitter.removeListener('connection',listener1)

 eventEmitter.emit('connection');

 eventListeners = require('events').EventEmitter.listenerCount(eventEmitter,'connection');
 console.log(eventListeners + " 个监听器监听连接事件。");

 console.log("程序执行完毕。");
 ```
### 其他示例
util.inherits(construtor,superConstrutor) 
从一个构造函数中继承原型方法到另一个。 constructor 的原型会被设置到一个从 superConstructor 创建的新对象上。可以通过constructor.super_查看superConstrutor
```js
    const util = require('util');
    const EventEmitter = require('events');

    function MyStream() {
      EventEmitter.call(this);
    }
    /**
     * EventEmitter
     * { [Function: EventEmitter]
     * EventEmitter: [Circular],
     * usingDomains: true,
     * defaultMaxListeners: [Getter/Setter],
     * init: [Function],
     * listenerCount: [Function] }
     * 
    */
    util.inherits(MyStream, EventEmitter);
   /**MyStream
    * { [Function: MyStream]
    *  super_:
    * { [Function: EventEmitter]
    *   EventEmitter: [Circular],
    *   usingDomains: true,
    *   defaultMaxListeners: [Getter/Setter],
    *   init: [Function],
    *   listenerCount: [Function] } }
   */
    MyStream.prototype.write = function(data) {
      this.emit('data', data);
    };

    const stream = new MyStream();

    console.log(stream instanceof EventEmitter); // true
    console.log(MyStream.super_ === EventEmitter); // true

    stream.on('data', (data) => {
      console.log(`接收的数据："${data}"`);
    });
    stream.write('运作良好！'); // 接收的数据："运作良好！"
```
