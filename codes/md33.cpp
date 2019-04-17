#include<ctime>
#include<cmath>
#include<iostream>
#include<algorithm>
#define INFINITE_DISTANCE 65535    // 无限大距离
#define COORDINATE_RANGE 100.0    // 横纵坐标范围为[-100,100]
using namespace std;

typedef struct Point
{
	double x;
	double y;
}Point;

Point pp;
int top=0; 
double Distance(Point a,Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool compareX(Point a,Point b)
{
	return a.x<b.x;
}

bool compareY(Point a,Point b)
{
	return a.y<b.y;
}
//最近点距离 
float ClosestPair(Point points[],int length,Point &a,Point &b)
{   
	double distance;
	double dl,dr;
	int k=0;
	Point al,ar,bl,br;
	if(length<=3)
	{
		if(length==1)
		   return INFINITE_DISTANCE;
	    else if(length==2)
	    {
	    	a=points[0];
	    	b=points[1];
	    	distance=Distance(points[0],points[1]);
		}else
		{
			double d1=Distance(points[0],points[1]);
			double d2=Distance(points[0],points[2]);
			double d3=Distance(points[1],points[2]);
			if(d1<d2&&d1<d3)
			{
			   distance=d1;
               a=points[0];
	           b=points[1];
			}else if(d2<d1&&d2<d3)
			{
			   distance=d2;
               a=points[0];
	           b=points[2];
			}else
			{
			   distance=d3;
               a=points[1];
	           b=points[2];
			}
		}
	}else{
		Point *pl=new Point[length/2];
		Point *pr=new Point[length-length/2];
		sort(points,points+length,compareX);
		double mid=points[length/2].x;
		for(size_t i=0;i<length/2;i++)
		{
			pl[i]=points[i];
		}
		for(size_t j=0,i=length/2;i<length;i++)
		   pr[j++]=points[i];
		   
	    dl=ClosestPair(pl,length/2,al,bl);
	    dr=ClosestPair(pr,length-length/2,ar,br);
	    
	    if(dl<dr){
	    	distance=dl;
	    	a=al;
	    	b=bl;
		}else{
			distance=dr;
	    	a=ar;
	    	b=br;
		}
		
		Point *pm=new Point[length];
		for(size_t i=0;i<length;i++)
		{
			if(abs(points[i].x-mid)<=distance)
			    pm[k++]=points[i];
		}
		
		sort(pm,pm+k,compareY);
		for(size_t i=0;i<k;i++)
		{
			if(pm[i].x-mid>=0)
			   continue;
			int x=0;
			for(size_t j=i+1;j<=i+6+x && j<k;j++)
			{
				if(pm[j].x-mid<0)
				{
					x++;
					continue;
				}
				if(Distance(pm[i],pm[j])<distance)
				{
					distance = Distance(pm[i], pm[j]);
                    a = pm[i];
                    b = pm[j];
				}
			}
		}
	}
    return distance;
}
double cross(Point p0,Point a,Point b)
{
	return (a.x-p0.x)*(b.y-p0.y)-(b.x-p0.x)*(a.y-p0.y); 
}

bool compareXY(Point a,Point b)
{
	double c=cross(pp,a,b);
	if(c==0)
	{
		return Distance(a,pp)<Distance(b,pp);
	}
	return c>0;
}
Point *Graham_Scan(Point Q[],int length)
{   
    Point *stacks= new Point[length];
    int m=0;
    for(size_t i=1;i<length;i++)
    {
    	if(Q[m].y>Q[i].y||(Q[m].y==Q[i].y&&Q[m].x<Q[i].x))
    	   m=i;
	}
	
	swap(Q[0],Q[m]);
	//cout<<Q[m].x<<Q[m].y<<endl;
	pp=Q[0];
	sort(Q+1,Q+length,compareXY);
	stacks[top++]=Q[0];
	stacks[top++]=Q[1];
	stacks[top++]=Q[2];
	for(size_t i=3;i<length;i++)
	{   
	    while(cross(stacks[top-2],stacks[top-1],Q[i])>0)
	    {
	    	top--;
		}
		stacks[top++]=Q[i];
	}
    return stacks;
} 
void SetPoints(Point *points, int length)
{//随机函数对点数组points中的二维点进行初始化
    srand(unsigned(time(NULL)));
    for (int i = 0; i < length; i++)
    {
        points[i].x = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        points[i].y = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
    }
}
int main()
{
    int num;            //随机生成的点对个数
    Point a, b;            //最近点对
    double diatance;    //点对距离
    
    cout << "请输入二维点对个数:";
    cin >> num;
    if (num < 2)
        cout << "请输入大于等于2的点个数！！" << endl;
    else
    {
        cout << endl << "随机生成的" << num << "个二维点对如下：" << endl;
        Point *points = new Point[num];
        SetPoints(points, num);
        for (int i = 0; i < num; i++)
            cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
        
        Point * ans=Graham_Scan(points,num);
        //diatance = ClosestPair(points, num, a, b);
        cout << endl << endl << "按横坐标排序后的点对:" << endl;
        for (int i = 0; i < top; i++)
            cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

        //cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" << "(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;
    }
    system("pause");
    return 0;
}

