#include <iostream>
#include <utility>
#include <vector>
//#include <float>
using namespace std;

pair<vector<vector<float>>, vector<vector<int>>> Option_Bst(const vector<float> &p,const vector<float> &q,int n) {
    vector<vector<float>> e(n+2,vector<float>(n+1,0)),w(n+2,vector<float>(n+1,0));
    vector<vector<int>> root(n+1,vector<int>(n+1,0));
    for(auto i=1;i<=n+1;i++)
    {
    	e[i][i-1]=q[i-1];
    	w[i][i-1]=q[i-1];      
	}
    for(auto l = 1; l <= n; l++) {
        for (auto i = 1; i <= n - l + 1; i++) {
            auto j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            if(i==j)
            {
            	e[i][j]=e[i][j-1]+e[i+1][j]+w[i][j];
            	root[i][j]=i;
			}else{
              for(auto r = root[i][j-1]; r <=root[i+1][j]; r++) {
            	auto t=e[i][r-1]+e[r+1][j]+w[i][j];
            	if(t<e[i][j])
            	{
            		e[i][j]=t;
            		root[i][j]=r;
				}
             } 
			}
        }
    }
    return make_pair(e, root);
}
void Option_Bst_Show(const vector<vector<float>> &e,const vector<vector<int>> &root,int n){
	for(auto i=1;i<n+2;i++){
		for(auto j=0;j<=n;j++)
	      cout<<e[i][j]<<'\t';
	    cout<<endl;
	}
    cout<<endl;
    for(auto i=1;i<=n;i++){
    	for(auto j=1;j<=n;j++)
	      cout<<root[i][j]<<'\t';
	    cout<<endl;
	}
	   
}

void Constuct_Optimal_Bst(const vector<vector<int>>&root,int i,int j)
{   
    auto r=root[i][j];
    cout<<r<<endl;
    if(i==j){//无子树 
     cout<<"left tree"<<i-1<<endl;
	 cout<<"right tree"<<j<<endl;
     return;
	}else if(r==i){//只有右子树 
	  cout<<"left tree"<<i-1<<endl;
	  cout<<"right tree: ";
	  Constuct_Optimal_Bst(root,r+1,j);
	}else if(r==j){//只有左子树 
      cout<<"left tree: ";
	  Constuct_Optimal_Bst(root,i,r-1);
	  cout<<"right"<<j<<endl;
	}else{
	  cout<<"left tree: ";
	  Constuct_Optimal_Bst(root,i,r-1);
	  cout<<"right tree: ";
      Constuct_Optimal_Bst(root,r+1,j);
	}
}
int main()
{  
    vector<float> p{0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
    vector<float> q{0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};
    auto ans=Option_Bst(p,q,7);
    Constuct_Optimal_Bst(ans.second,1,7);
    Option_Bst_Show(ans.first,ans.second,7);
	return 0;
}
