#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define db double
using namespace std;

const int maxn = 205;
const db inf = 1e9;

class TSP{
public:
    int n;
    db x[maxn],y[maxn],dis[maxn][maxn],dp[maxn][maxn];

    db cal(db x1,db x2,db y1,db y2){return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

    void sove(){
        dp[1][2]=dis[1][2];
        for(int j=3;j<=n;j++){
            // i<j-1
            for(int i=1;i<=j-2;i++)dp[i][j]=dp[i][j-1]+dis[j-1][j];
            //i=j-1
            db Min=inf;
            for(int k=1;k<=j-2;k++)Min=min(Min,dp[k][j-1]+dis[k][j]);
            dp[j-1][j]=Min;
        }
        dp[n][n]=dp[n-1][n]+dis[n-1][n];
        printf("%.2lf\n",dp[n][n]);
    }

    int init(){
       if(scanf("%d",&n)==-1)return -1;
       for(int i=1;i<=n;i++)scanf("%lf%lf",&x[i],&y[i]);
       for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=cal(x[i],x[j],y[i],y[j]);
       sove();
    }

}tp;

int main()
{
    while(~tp.init());
    return 0;
}
