#include<iostream>
using namespace std;

class Base
{
public:
    virtual void fun1()
    {
        cout << "Base::func1()" << endl;
    }
    virtual void fun2()
    {
        cout << "Base::func2()" << endl;
    }
private:
    int b;
};
class Derive :public Base
{
public:
    virtual void fun1()           //重写基类虚函数,实现多态
    {
        cout << "Derive::func1()" << endl;
    }

    virtual void fun3()
    {
        cout << "Derive::func3()" << endl;
    }
    void fun4()
    {
        cout << "Derive::func4()" << endl;
    }
private:
    int d;
};

int main()
{
	Derive a;
	system("pause");
	return 0;
}
