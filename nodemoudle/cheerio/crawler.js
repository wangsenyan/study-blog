
/**
 * 批量添加注释
 */
//var cheerio=require('cheerio');
var http = require('http');
var iconv = require('iconv-lite');
var fs = require('fs');
var url = 'http://discuzt.cr180.com/discuzcode-db.html';
http.get(url, function (sres) {
  var chunks = [];
  sres.on('data', function (chunk) {
    chunks.push(chunk);
  });
  sres.on('end', function () {
    var html = iconv.decode(Buffer.concat(chunks), 'utf8');
    var first = html.indexOf('class="cr180_dbtable"');
    var last = html.indexOf('div', html.lastIndexOf('class="cr180_dbtable"'));
    var html0 = html.substring(first - 5, last + 4)
    var htmlArrays = html0.split('<div class="cr180_dbtable">');
    //var database = [];
    //var dbUnchange = [];
    var sql = "";
    fs.readFile('./Dump20181113.sql', 'utf8', function (e, file) {
      var r = file;
      var length = htmlArrays.length;
      for (var i = 1; i < length; i++) {

        var htmlArray = htmlArrays[i];
        var table = htmlArray.substring(htmlArray.indexOf('<h2>') + 4, htmlArray.indexOf('<span'))
        var comment = htmlArray.substring(htmlArray.indexOf('cr_tip') + 8, htmlArray.indexOf('</span>'))
        var comments = comment.substring(0, comment.indexOf('<') == -1 ? comment.length : comment.indexOf('<'));
        //初始值
        var paramIndexStart = htmlArray.indexOf('cr_name');
        var paramIndexEnd = htmlArray.indexOf('</td>', paramIndexStart);
        var discIndexStart = htmlArray.indexOf('cr_dec');
        var discIndexEnd = htmlArray.indexOf('</td>', discIndexStart);
        // tb['table'] = table;
        // tb['comments'] = comments;
        var begStr = "CREATE TABLE `" + table + "`";
        var index = r.indexOf(begStr)
        var begin = r.indexOf('(', index) + 1;
        var index1 = r.indexOf(';', index);
        var tableTemp = r.substring(begin, index1);
        var end = Math.min(tableTemp.indexOf('PRIMARY'), tableTemp.indexOf('KEY'));
        var table0 = tableTemp.substring(0, end);
        var colunms = table0.split(',');
        // console.log(colunms);
        while (paramIndexStart != -1) {
          var param = htmlArray.substring(paramIndexStart + 9, paramIndexEnd);
          var disc = htmlArray.substring(discIndexStart + 8, discIndexEnd);
          var regp = new RegExp('`' + param + '`');
          // console.log(param)
          for (var j = 0; j < colunms.length - 1; j++) {
            var colunm = colunms[j];
            if (colunm.indexOf(param) != -1) {
              var coltemp = colunm.replace(/(\n|\r|(\r\n)|(\u0085)|(\u2028)|(\u2029))/g, "").replace(regp, "`" + param + "` " + "`" + param + "`");
              if (coltemp.indexOf('COMMENT') != -1) {
                coltemp = coltemp.split('COMMENT')[0];
              }
              var sqlOne = "ALTER TABLE `ultrax`." + "`" + table + "` CHANGE COLUMN " + coltemp + " " + " COMMENT '" + disc + "'" + ";" + "\n";
              sql += sqlOne;
            }
          }
          paramIndexStart = htmlArray.indexOf('cr_name', paramIndexStart + 9);
          paramIndexEnd = htmlArray.indexOf('</td>', paramIndexStart);
          discIndexStart = htmlArray.indexOf('cr_dec', discIndexStart + 8);
          discIndexEnd = htmlArray.indexOf('<', discIndexStart);
          //tb[param] = disc;
        }
        //database.push(tb);
      }
      //console.log(sql)
      fs.writeFile('./sql.sql', sql, function (e, r) {
        console.log(e ? e : "success");
        process.exit(e ? 0 : 1);
      })
    })
  })
})

// fs.readFile('./sql.sql', 'utf8', function (e, r) {
//   if (e) {
//     console.log(e);
//     process.exit(0);
//   }
//   var columns = r.split(";");
//   // fs.close('./sql.sql');
//   //console.log(columns)
//   var all = "";
//   for (var i = 0; i < columns.length - 1; i++) {
//     var column = columns[i];
//     //console.log(column)
//     var temp = column.indexOf("COLUMN");
//     var start = column.indexOf("`", temp);
//     var end = column.indexOf("`", start + 1);
//     var word = column.substring(start, end + 1);
//     var reg = new RegExp(word);
//     // console.log(column.match(reg))
//     all += column.replace(reg, word + " " + word) + ";" + "\n";
//   }
//   fs.writeFile('./mid.sql', all, function (e, r) {
//     console.log(e ? e : "success");
//     process.exit(e ? 0 : 1);
//   })
// })