## <center>NPM</center>

### 基本命令

```sh
# 仅安装package.json中的dependences里面的包
npm install --production  --registry [source]
# npm会自动把node_modules/.bin加入$PATHs
npm run [option]
# 相当于npm run test
npm test
# 相当于npm run start
npm start
```
for example:

```json
{
  "name": "my-silly-app",
  "version": "1.2.3",
  "private": true,
  "dependencies": {
    "browserify": "~2.35.2",
    "uglifyjs": "~2.3.6"
  },
  "devDependencies": {
    "watchify": "~0.1.0",
    "catw": "~0.0.1",
    "tap": "~0.4.4"
  },
  "scripts": {
    "build-js": "browserify browser/main.js | uglifyjs -mc > static/bundle.js",
    "build-css": "cat static/pages/*.css tabs/*/*.css",
    "build": "npm run build-js && npm run build-css",
    "watch-js": "watchify browser/main.js -o static/bundle.js -dv",
    "watch-css": "catw static/pages/*.css tabs/*/*.css -o static/bundle.css -v",
    "watch": "npm run watch-js & npm run watch-css",
    "start": "node server.js",
    "test": "tap test/*.js"
  }
}
```