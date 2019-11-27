/**
 * 自动生成api文档
 * @param {string} param "a+b+c" a类型b解释c测试值
 * 调用方式
 * ```
 *  let apidoc=require('../utils/apidoc')
 *  let file=apidoc.parserFile('a.js')
 *  apidoc.inputFile(file[1]);
 * ```
 * 在test目录下生成两份文件
 */
const iconv = require("iconv-lite");
const fs = require("fs");
const path = require("path");
const request = require("request").defaults({ jar: true });
const async = require('async');
const baseUrl = "http://localhost:8001";
const Cookie = "connect.sid=s%3ACtyUiqcoTl1dWTEJPIFWeqvG6bHtObFZ.bZYWVB%2FNk%2BMoOYu8JpEP%2BqykODnu3PPr0LuTDQFOCj4; username=gaoang; userid=1; rid=1; node_admin=s%3A1%24%24%24%24.eSiPw2iXoD1HyCsme3HoGVJLBYXYQqA5Q1FBv2KfNZc";
const Regs = {
  docBlocksRegExp: /\/\*\*\uffff?(.+?)\uffff?(?:\s*)?\*\//g,
  inlineRegExp: /^(\s*)?(\*)[ ]?/gm,
  elementsRegExp: /@\w*\s?\{(\w+)\}\s?(\S+)\s?(.+?)(?=\uffff[\s\*]*@|$)/gm
}
class ApiDoc {
  constructor() { }
  static parserFile(sour) {
    const sfile = path.join(__dirname, "..", "routes", sour);
    const dfile = path.join(__dirname, "..", "test", "api_" + sour.split('.')[0]);
    const applyFile = dfile + "_apply.json";
    const reqFile = dfile + "_req.json";
    const fileContent = fs.readFileSync(sfile, { encoding: 'binary' });
    let src = iconv.decode(fileContent, 'utf8');
    src = src.replace(/\r\n/g, '\n');
    const blocks = findBlocks(src);
    const elements = blocks.map(function (block) {
      const elements = findElements(block);
      return elements;
    })
    const apply_elements = makeTestEles(elements);
    const req_emelents = makeApiEles(elements);
    fs.writeFileSync(applyFile, JSON.stringify(apply_elements), { encoding: "utf8" });
    fs.writeFileSync(reqFile, JSON.stringify(req_emelents), { encoding: "utf8" });
    return [applyFile, reqFile];
  }
  static inputFile(file) {
    fs.readFile(file[0], 'utf8', function (e, r) {
      const contents = JSON.parse(r);
      const cons = [];
      async.forEachSeries(contents, function (content, callback) {
        getReturn(content, function (e, r) {
          if (e) return callback(e);
          //console.log(r)
          content.return = deepClone(r);
          cons.push(content);
          callback(null)
        })
      }, function () {
        fs.writeFileSync(file[0], JSON.stringify(cons), { encoding: "utf8" });
      })
    })
  }
}

function findBlocks(content) {
  const blocks = [];
  let src = content;
  src = src.replace(/\n/g, '\uffff');
  let matches = Regs.docBlocksRegExp.exec(src);
  while (matches) {
    let block = matches[2] || matches[1];
    block = block.replace(Regs.inlineRegExp, '');
    blocks.push(block);
    matches = Regs.docBlocksRegExp.exec(src);
  }
  return blocks;
}

function findElements(block) {
  const element = {};
  block = block.replace(/\n/g, '\uffff');
  let matches = Regs.elementsRegExp.exec(block);
  while (matches) {
    if (matches.index == 0) {
      element[matches[1]] = matches[2];
      matches = Regs.elementsRegExp.exec(block);
      continue;
    }
    element[matches[2]] = matches[1] + "+" + matches[3];
    matches = Regs.elementsRegExp.exec(block);
  }
  return element
}
//測試用例
function makeTestEles(elements) {
  let elemTep = JSON.parse(JSON.stringify(elements));
  elemTep = elemTep.map(function (block) {
    const element = block;
    for (const i in element) {
      if (i == 'post' || i == 'get')
        continue;
      element[i] = element[i].split('+')[2] || "";
    }
    return element;
  })
  return elemTep;
}
function makeApiEles(elements) {
  let elemTep = JSON.parse(JSON.stringify(elements));
  elemTep = elemTep.map(function (block) {
    const element = block;
    let count = 0;
    for (const i in element) {
      if (i == 'post' || i == 'get') {
        count++;
        continue;
      }
      const elem = element[i].split('+');
      element[i] = elem[0] + "|" + elem[1]
    }
    console.log(count)
    return count == 0 ? "" : element;
  })
  return elemTep;
}

function getReturn(element, cb) {
  const method = element['get'] ? "get" : "post";
  const path = element['get'] || element['post'] || null;
  if (!path) {
    return cb('e')
  }
  const query = concat(element);
  let url = baseUrl + path;
  if (query) {
    url = baseUrl + path + "/?" + query;
  }
  const opt = {
    method: method,
    url: url,
    headers: {
      "Accept": "application/json, text/javascript, */*; q=0.01",
      "X-Requested-With": "XMLHttpRequest",
      "content-type": "application/json",
      "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.110 Safari/537.36",
      "Cookie": Cookie
    },
    form: element
  }
  request(opt, function (e, r, b) {
    if (e) {
      console.log(opt, e)
      return cb(e + opt)
    }
    return cb(null, JSON.parse(b))
  })
}
function concat(element) {
  const query = []
  for (const i in element) {
    if (element[i] && i != 'get' && i != 'post') {
      query.push(i + "=" + element[i]);
    }
  }
  return query.join('&');
}

function deepClone(element) {
  if (element instanceof Array) {
    element = element.slice(0, 1)
    element[0] = deepClone(element[0]);
    return element;
  } else {
    for (const i in element) {
      if (element[i] instanceof Object) {
        element[i] = deepClone(element[i]);
      }
    }
    return element;
  }
}

module.exports = ApiDoc
