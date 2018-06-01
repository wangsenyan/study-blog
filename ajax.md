   
   ``` 
   browser-----create an XMLHttpRequest object----send HttpRequest
   internet-----Process HTTPRequest ----create a response and send data back to  the browser
   browser----Process the returned data using JavaScript ----update page content
   ```
```js
function loadXMLDoc()
{
	var xmlhttp;
	if (window.XMLHttpRequest)
	{
		//  IE7+, Firefox, Chrome, Opera, Safari 浏览器执行代码
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		// IE6, IE5 浏览器执行代码
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById("myDiv").innerHTML=xmlhttp.responseText;
		}
	}
	xmlhttp.open("GET","/try/ajax/ajax_info.txt",true);
	xmlhttp.send();
```
### 避免缓存，向url添加一个唯一的ID
```js
xmlhttp.open("GET","/try/ajax/demo_get.php?t=" + Math.random(),true);
```
### Html那样post数据，使用setRequestHeader（）添加http头
```js
xmlhttp.open("POST","/try/ajax/demo_post2.php",true);
xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
xmlhttp.send("fname=Henry&lname=Ford");
open(method,url,async)
```
### async为true或false，等待时候xmlhttp.readyState==4情况不一样
