### 安装
```sh
npm install express --save
express --help
express --pug
```
### 使用
```js
  app.engine('pug', require('pug').__express) //new
  app.set('views', path.join(__dirname, 'views'));
  app.set('view engine', 'pug');

  NODE_ENV=production node app //unix
  set NODE_ENV=production //windows
  process.env //默认为开发环境 development、stage、test、production
  app.configure()
  app.set()
  app.get()
  app.enable()
  app.disable()

  app.enable(setting) ===app.set(setting,true)
  app.disable(setting)===app.set(setting,false)

  app.set('views',__dirname+'/views')
  //绝对路劲->识图目录->index
```
### 代码

```js
  session = require('connect -session')
  cookieParser = require('cookie-parser')
  app = express()
  app.use(cookieParser);
  app.use(session({
    secret: 'wangsenyan',
    store: new mongoStore({
      url: dbUrl,
      collection: 'sessions'
    }),
    resave: false,
    saveUninitialized: true
  }))

  //cookie-parser从客户端取cookie，然后经过express-session（以express为本）的处理。在客户端表示为一个签名后的字符串，在服务端，由于使用了unsign方法，所以能看到解签过的字符。

```
