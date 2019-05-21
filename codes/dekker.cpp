#include<iostream>
//Dekker算法
bool flag[2];//提供所有进程的状态
int turn;//表示哪个进程应坚持进入
void p0()
{
	while(true)
	{
		flag[0]=true;//P0想使用临界区
		while(flag[1])//P1也想使用
			if(turn==1)//确实轮到了P1使用
			{
				flag[0]=false;//P0取消请求
				while(turn==1)
					/*什么也不做*/
				flag[0]=true;//P1用完后，P0继续发出请求
			}
			//临界区
			flag[0]=false;//p0用完了
			turn=1;//将权限移交给P1
			//其余部分
	}
}
void p1()
{
	while(true)
	{
		flag[1]=true;
		while(flag[0])
			if(turn==0)
		{
			flag[1]=false;
			while(turn==0)
				/*什么也不做*/
			flag[1]=true;	
		}
		flag[1]=fasle;
		turn=0;
	}
}
void main()
{
	turn=0;
	flag[0]=false;
	flag[1]=false;
	perbegin(p0(),p1());
	return 0;
}
