### ctype

```cpp
#include <cctype>
isalpha()  //是否是字母
isdigits() //是否是数字
isspace() //是否空白
ispunct() //是否为标点符号
```
![cctype](../image/cctype.png)

```cpp
(i < 2) ? !i ? x[i] : y : x[1]
===
(i < 2) ?( !i ? x[i] : y ): x[1]
```
* 文件I/O

```cpp
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ofstream outFile; //定义ofstream对象
	outFile.open("fish.text"); //不存在则新建，否则截断将改对象和特定文件关联
	outFile.precision(2) //设定输出浮点数的精度值
	outFile.setf(ios_base::showpoint);//强制显示小数点输出
	char filename[50];
	cin>>filename;
	fout.open(filename);
}
```
* setf() 设置各种格式化状态,返回调用它之前有效的所有格式化设置
* ios_base::fixed 将对象至于使用定点表示法的模式
* ios_base::showpoint 仅对象置于显示小数点的模式，即使小数部分为零
* width()设置下一次输出操作使用的字段宽度，只下一次有效
* ios_base::fmtflags
是存储这种信息所需的数据类型名称，存储格式化设置
```cpp
ios_base::fmtflags initial
initial = os.setf(ios_base::fixed);
os.setf(initial);
```