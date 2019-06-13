#include<iostream>
#include<string>
#define page 4096

int main(int argv,char *argc[])
{   
    int a=2,b;
	b=2+(a+=a++,a+5,++a);
	std::cout<<b<<std::endl;
	if(argv<2)
	{ 
	   std::cout<<"required argument!";
	   exit(0);
	}
	long long address=atoll(argc[1]);
	if(address>4294967295)
	{
		std::cout<<"invalid address!";
		exit(0);
	}
	std::cout<<"The address "<< address<<" contains:"<<std::endl;
	std::cout<<"page number = "<< address/page<<std::endl;
	std::cout<<"offset = "<< address%page<<std::endl;
	return 0;
}
