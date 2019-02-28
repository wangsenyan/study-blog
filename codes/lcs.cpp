#include <iostream>
#include <utility>
#include <vector>
using namespace std;
//vector<char> temp_VecX{'A','B','C','D'};
//vector<char> temp_VecY{'A','B','C','D'}; 
//pair<vector<vector<int>>, vector<vector<char>>> Lcs_Length(const vector<char> &X,const vector<char> &Y) {
//    auto m =X.size();
//    auto n = Y.size();
//    vector<vector<int>> B;
//	vector<vector<char>> C;
//
//    B.resize(temp_m+1);
//    C.resize(temp_m+1);
//
//    for(auto &i : B) {
//        i.resize(n+1);
//    }
//    for (auto &i : C) {
//        i.resize(n + 1);
//    }
//    for(auto i = 1; i <= m; ++i) {
//        C[i][0] = 0;
//    }
//    for(auto i = 0; i <= n; ++i) {
//        C[0][i] = 0;
//    }
//    for(auto i=1;i<=m;i++){
//    	for(auto j=1;j<=n;j++)
//    	{
//    		if(X[i]==Y[j])
//    		{
//    			C[i][j]=C[i-1][j-1]+1;
//    			B[i][j]='\';
//			}
//			else if(C[i-1][j]>=C[i][j-1])
//			{
//				C[i][j]=C[i-1][j];
//				B[i][j]='|';
//			}else
//			{
//				C[i][j]=C[i][j-1];
//				B[i][j]='-';
//			}
//		}
//	}
//    return make_pair(C, B);
//}
//
//char Print_Lcs(vector<vector<int>> B,const vector<char> &X,int i,int j)
//{
//	if(i==0 || j==0)
//	 return;
//	if(B[i][j]=='\')
//	{
//		Print_Lcs(B,X,i-1,j-1);
//		cout<<X[i]<<endl;
//	}else if(b[i][j]=='|')
//	   Print_Lcs(B,X,i-1,j);
//	else
//	   Print_Lcs(B,X,i,j-1);
//}
