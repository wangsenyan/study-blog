1. 点选择 id [属性] find()
2. 线选择 class tag has() 可以叠加很多层
2. 关系选择 this/children()/parent()/next()/siblings()/
  当前元素 $('this') $('#this') $('.this') 
  群组a,b,c{} 后代a b{} 通配符*{}
3. 特殊选择 end() 
4. has()包含本元素
  find()不包含本元素
  end()跳出最近的选择器集合
  siblings()相邻的其他元素
  .is(selector)匹配的话返回true
5. innerHTML 所选元素之间的html/html()
6. 在jQuery对象无法使用DOM对象的任何方法,jquery后面都带（）
  jQuery和DOM转换var $cr=$("#cr") var cr=$cr[0]/$cr.get(0)
  Dom转JQuery var cr=document.getElemenntById("cr");var   $cr=$(cr)  即$()包含dom元素
7. jQuery不必判断DOM是否存在
8. document.querySelectorAll() 返回选定的全部元素，是数组
  document.querySelector() 返回找到的第一个元素
