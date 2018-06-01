## 正则表达式
### 常见正则
```js
  var re = {
  email: /^\w+@[a-z0-9]+(\.[a-z]+){1,3}$/,
  number: /\d+/,
  tel: /\d{3}-\d{4}-\d{4}/,
  http: /[a-zA-Z]+:/ / [^\s] * /,
	postcode: /[1-9]\d{5}/,
  id: /[1-9]\d{14}|[1-9]\d{17}|[1-9]\d{16}x/,
  china: /^[\u4e00-\u9fa5]{0,}$/,
  yuming: /[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(/.[a - zA - Z0 - 9]{ 0, 62})+/.?/,
  password : /^[a-zA-Z]\w{5,17}$/,
  Uid : /^[a-zA-Z][a-zA-Z0-9_]{4,15}$/,
  data : /^\d{4}-\d{1,2}-\d{1,2}/,
  time: /^(?:19|20)[0-9][0-9]-(?:(?:0[1-9])|(?:1[0-2]))-(?:(?:[0-2][1-9])|(?:[1-3][0-1])) (?:(?:[0-2][0-3])|(?:[0-1][0-9])):[0-5][0-9]:[0-5][0-9]$/
 }

 'industry,industries'.match(/industr(?:y|ies)/g)['industry', 'industries']
```
### 正则元素
```
  \s : 空格 \S :非空格
  \d : 数字 \D :非数字
  \w : 字符 \W :非字符例子
  () : 分组符
  +  :匹配（1,）
  .   任意字符
  \.  真正的点
  \b  独立的部分（起始，结束，空格）
  \B  非独立的部分
```
### replace() 用法

```js
  var str = "我爱北京天安门，天安门上太阳升。";
  var re = /北京|天安门/g;  //  找到北京 或者天安门 全局匹配
  var str2 = str.replace(re,function(str){
                alert(str); //用来测试：函数的第一个参数代表每次搜索到的符合正则的字符，所以第一次str指的是北京 第二次str是天安门 第三次str是天安门
              var result = '';
              for(var i=0;i<str.length;i++){
                  result += '*';
              }              
              return result; //所以搜索到了几个字就返回几个* 
          });
  alert(str2)
  var str = '2013-6-7';var re = /(\d+)(-)/g;
  str2 = str.replace(re,function($0,$1,$2){return $1+'.';});
  alert(str2);
  //返回2013.6.7

  function getByClass(parent,classname){
    if(parent.getElementsByClassName){
      return parent.getElementsByClassName(classname);
    }else{
      var arr = [];
      var aEle = parent.getElementsByTagName('*');
      var re = new RegExp('\\b'+classname+'\\b');
      for(var i = 0; i<aEle.length;i++){
        if(re.test(aEle[i].className)){
          arr.push(aEle[i]);
          }  
        }
      return arr;
    }
  }
```
