'use strict';
const babel = require('babel-core');
const result = babel.transform('foo===bar;n*n;', {
  plugins: [
    require('./example'),
  ],
});
console.log(result.code);
