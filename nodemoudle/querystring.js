//解析和格式化URL查询字符串
const querystring = require('querystring');
//querystring.escape(str)
const params={
    a:"xx",
    b:"yy",
    c:{
        c1:"zzz",
        c2:"kkk"
    }
};
console.log(querystring.stringify(params,'','='))
/**
 *querystring.parse(str[,sep[,eq[,options]]]) utf-8默认
 *str <string>
 *sep <string>
 *eq  <string>
 *options <Object>
 *  decodeURIComponent <function> 默认querystring.unescape()
 *  maxKey <number> 解析的键的最大数量，默认1000,0为不限制
 */
 console.log(querystring.parse("foo=bar&abc=xyz&abc=123"))
/** 假设存在 gbkDecodeURIComponent 函数。
 querystring.parse('w=%D6%D0%CE%C4&foo=bar', null, null,
 { decodeURIComponent: gbkDecodeURIComponent });
*/
/**querystring.stringify(obj[,sep[,eq[,options]]])
 *obj <Object>
 *sep <string> 默认"&" 键值对之间
 *eq  <string> 默认"=" 键与值
 *options
 * encodeURIComponent <function> 默认为querystring.escape()
 */


