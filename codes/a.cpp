#include<iostream>
#include<string>
#include<vector>



using namespace  std;
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        vector<int> bg=new vector<int>(1,1);
        for(int i=0;i<numRows;i++){
          vector<int> irow;
          irow.push(1);
          for(int j=1;j<i-1;j++){
            irow.push(bg[i]+bg[i-1]);
          }
          irow.push(1);
          bg=irow;
          res.push(irow);
        }
        return res;
    }
};
int main(int argv,char *argc[])
{       int num = 10;
        Solution s = new Solution;
            int numRows = 2;
            vector<vector<int>> r =  s.generate(numRows);
            for(int i=0;i<numRows;i++){
                for(int j=0;j<i;j++){
                    cout<<r[i][j];
                }
                cout<<endl;
            }
	return 0;
}
