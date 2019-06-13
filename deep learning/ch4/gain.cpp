#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
double Gain_max(vector<vector<double>> D, int i);
int main()
{
  vector<vector<double>> D = {
      {0.697, 0.460, 1},
      {0.774, 0.376, 1},
      {0.634, 0.264, 1},
      {0.608, 0.318, 1},
      {0.556, 0.215, 1},
      {0.403, 0.237, 1},
      {0.481, 0.149, 1},
      {0.437, 0.211, 1},
      {0.666, 0.091, 0},
      {0.243, 0.267, 0},
      {0.245, 0.057, 0},
      {0.343, 0.099, 0},
      {0.639, 0.161, 0},
      {0.657, 0.198, 0},
      {0.36, 0.37, 0},
      {0.593, 0.042, 0},
      {0.719, 0.103, 0}};
  cout << Gain_max(D, 1);
  return 0;
}
//统计第i行数据,连续数据 
double Gain_max(vector<vector<double>> D, int i)
{
  vector<double> Di;
  vector<double> T;
  int wd = D[0].size();
  int hg = D.size();
  double mi = 1;
  double sp = 0;
  for (int j = 0; j < D.size(); j++)
  {
    Di.push_back(D[j][i]);
  }
  sort(Di.begin(), Di.end());
  for (int j = 0; j < Di.size() - 1; j++)
  {
    T.push_back((Di[j] + Di[j + 1]) / 2);
    //cout<<(Di[j] + Di[j + 1]) / 2<<endl;
  }
  for (int j = 0; j < T.size(); j++)
  {
  	vector<vector<int>> p(2, vector<int>(2, 0));
    for (int k = 0; k < D.size(); k++)
    {
      if (D[k][i] <= T[j])
      {
        if (D[k][wd - 1] == 0)
          p[0][0]++;
        else
          p[0][1]++;
      }
      else
      {
        if (D[k][wd - 1] == 0)
          p[1][0]++;
        else
          p[1][1]++;
      }
    }
    double y = 0;
    for (int k = 0; k < p.size(); k++)
    {
      double x=0;
      double m = p[k][0] + p[k][1];
      x+=p[k][0]>0?(-p[k][0] / m * log2(p[k][0] /m)):0;
      x+=p[k][1]>0?(-p[k][1] / m * log2(p[k][1] /m)):0;
      x*=(m/hg);
      y+=x;
      //cout<<T[j]<<" "<<m<<" "<<p[k][0]<<" "<<p[k][1]<<" "<<log2(p[k][0] /m)<<" "<< log2(p[k][1] / m)<<endl;
      //x += (m / hg) * (-p[k][0] / m * log2(p[k][0] /m) - p[k][1] /m * log2(p[k][1] / m));
    }
    mi = y <=mi ? y : mi;
    sp = y <=mi ? T[j]:sp;
    //cout << y << endl;
  }
  return sp;
}
