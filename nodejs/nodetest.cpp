#include<iostream>
#include<vector>
using namespace std;
template<typename T>
struct my_is_void{
    static const bool value = false;
};
template<>
struct my_is_void<void>{
    static const bool value = true;
};
template<typename T>
struct my_is_pointer {
	static const bool value= false;
};
template<typename T>
struct my_is_pointer<T *>{
	static const bool value=true;
};

template<typename T>
typename T::value_type top(const T &c){
	if(!c.empty())
	   return c.back();
	else 
	   return typename T::value_type();
}

template<class IterT>
struct my_iterator_traits {
	typedef typename IterT::value_type value_type;
};	

template<class IterT>
struct my_iterator_traits<IterT*>{
	typedef IterT value_type;
};
void fun(int a) {
cout << "fun(int) is called" << endl;
}

void fun(double a) {
    cout << "fun(double) is called" << endl;
}

void fun(char a) {
    cout << "fun(char) is called" << endl;
}
int main(void)
{
    //my_is_void<bool>t1;
    //cout<<t1.value<<endl;
    //my_is_void<void>t2;
    //cout<<t2.value<<endl;
    //my_is_pointer<int> p1;
    //cout<<p1.value<<endl;
    //my_is_pointer<int *>p2;
    //cout<<p2.value<<endl;
    //vector<int> vec;
    //vec.push_back(1);
    //vec.push_back(2);
    //vec.push_back(3);
    //cout<<vec.value_type()<<endl;
    //cout<<top<vector<int>>(vec)<<endl;

	my_iterator_traits<vector<int>::iterator>::value_type a;
	fun(a);  // Êä³ö fun(int) is called
	my_iterator_traits<vector<double>::iterator>::value_type b;
	fun(b);  // Êä³ö fun(double) is called
	my_iterator_traits<char*>::value_type c;
	fun(c);  // Êä³ö fun(char) is called

    return 0;
}


