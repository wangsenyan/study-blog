#启动
 node inspect myscript.js
#repl运行代码
#cont,c -继续执行
#next,n -下一步
#step,s -跳进函数
#out,o -跳出函数
#pasue -暂停运行代码
#help
#enter且不输入命令，则可重复上一个调试命令
断点
#setBreakpoint(),sb() -在当前行设置断点
#setBreakpoint(line),sb(line) -在指定行设置断点
#setBreakpoint('fn()'),sb(...) -在函数体的第一条语句设置断点
#setBreakpoint('script.js',1),sb(...) -在script.js的第一行设置断点
#clearBreakpoint('script.js', 1), cb(...) - 清除 script.js 第 1 行的断点

#node --inspect index.js 用chorme