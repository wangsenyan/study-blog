#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int binary_search(vector<int> l, int a);
void show(vector<int> list);
class Disk_Seek
{
private:
  int total;
  int first;
  double x;
  double y;
  double t;
  int bg;
  int ed;

public:
  Disk_Seek(int f, double a, double b, int c, int d)
  {
    total = 0;
    t = 0;
    first = f;
    x = a;
    y = b;
    bg = c;
    ed = d;
  };
  //~Disk_Seek();
  vector<int> FCFS(vector<int> list);
  vector<int> SSTF(vector<int> list);
  vector<int> SCAN(vector<int> list);
  vector<int> C_SCAN(vector<int> list);
  vector<int> LOOK(vector<int> list);
  vector<int> C_LOOK(vector<int> list);
  void SHOW(string s);
  void INIT();
  double SEEK_TIME(int l);
};

double Disk_Seek::SEEK_TIME(int l)
{
  return (x + y * sqrt(double(l)));
}
vector<int> Disk_Seek::FCFS(vector<int> list)
{
  vector<int> res = list;
  int ft = first;
  for (int i = 0; i < list.size(); i++)
  {
    int dist = abs(list[i] - ft);
    total += dist;
    t += SEEK_TIME(dist);
    ft = list[i];
  }
  return res;
}
vector<int> Disk_Seek::SSTF(vector<int> list)
{
  int ft = first;
  int m = list.size();
  vector<int> res;
  sort(list.begin(), list.end());
  for (int i = 0; i < m; i++)
  {
    int dist = INT_MAX;
    int k = 0;
    for (int j = 0; j < m; j++)
    {
      if (list[j] != -1)
      {
        int tmp = abs(list[j] - ft);
        if (tmp < dist)
        {
          dist = tmp;
          k = j;
        }
      }
    }
    total += dist;
    t += SEEK_TIME(dist);
    ft = list[k];
    list[k] = -1;
    res.push_back(ft);
  }
  return res;
}
//电梯算法
vector<int> Disk_Seek::SCAN(vector<int> list)
{
  vector<int> res;
  list.push_back(ed);
  sort(list.begin(), list.end());
  int ft = first;
  int s = binary_search(list, ft);
  //cout<<list[s]<<" "<<first<<endl;
  s = list[s] > first ? s : s + 1;
  for (int i = s; i < list.size(); i++)
  {
    int tmp = abs(list[i] - ft);
    total += tmp;
    t += SEEK_TIME(tmp);
    ft = list[i];
    res.push_back(ft);
  }
  for (int i = s - 1; i >= 0; i--)
  {
    int tmp = abs(list[i] - ft);
    total += tmp;
    t += SEEK_TIME(tmp);
    ft = list[i];
    res.push_back(ft);
  }
  return res;
}
vector<int> Disk_Seek::C_SCAN(vector<int> list)
{
  vector<int> res;
  list.push_back(bg);
  list.push_back(ed);
  int m = list.size();
  sort(list.begin(), list.end());
  int ft = first;
  int s = binary_search(list, ft);
  s = list[s] > first ? s : s + 1;
  for (int i = s; i < s + m; i++)
  {
    int tmp = abs(list[i % m] - ft);
    total += tmp;
    t += SEEK_TIME(tmp);
    ft = list[i % m];
    res.push_back(ft);
  }
  return res;
}
vector<int> Disk_Seek::LOOK(vector<int> list)
{
  vector<int> res;
  sort(list.begin(), list.end());
  int ft = first;
  int s = binary_search(list, ft);
  s = list[s] > first ? s : s + 1;
  for (int i = s; i < list.size(); i++)
  {
    int tmp = abs(list[i] - ft);
    total += tmp;
    t += SEEK_TIME(tmp);
    ft = list[i];
    res.push_back(ft);
  }
  for (int i = s - 1; i >= 0; i--)
  {
    int tmp = abs(list[i] - ft);
    total += tmp;
    t += SEEK_TIME(tmp);
    ft = list[i];
    res.push_back(ft);
  }
  return res;
}
vector<int> Disk_Seek::C_LOOK(vector<int> list)
{
  vector<int> res;
  int m = list.size();
  sort(list.begin(), list.end());
  int ft = first;
  int s = binary_search(list, ft);
  s = list[s] > first ? s : s + 1;
  for (int i = s; i < s + m; i++)
  {
    int tmp = abs(list[i % m] - ft);
    total += tmp;
    t += SEEK_TIME(tmp);
    ft = list[i % m];
    res.push_back(ft);
  }
  return res;
}
void Disk_Seek::SHOW(string s)
{
  cout << s << endl;
  cout << "seek distances " << total << endl;
  cout << "seek times " << t << endl;
  cout << endl;
}
void Disk_Seek::INIT()
{
  total = 0;
  t = 0;
}
int binary_search(vector<int> l, int a)
{
  int s = 0, e = l.size() - 1;
  if (s == e)
    return s;
  int m;
  while (s < e)
  {
    m = (s + e) / 2;
    if (l[m] == a)
      return m;
    else if (l[m] > a)
      e = m - 1;
    else
      s = m + 1;
  }
  return abs(l[m + 1] - a) > abs(a - l[m]) ? m : m + 1;
}
void show(vector<int> list)
{
  for (auto i : list)
    cout << i << '\t';
  cout << endl;
}

int main()
{
  vector<int> ep = {2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681};
  Disk_Seek sk(2150, 0.76, 0.24, 0, 4999);
  show(sk.FCFS(ep));
  sk.SHOW("FCFS");
  sk.INIT();
  show(sk.SSTF(ep));
  sk.SHOW("SSTF");
  sk.INIT();
  show(sk.SCAN(ep));
  sk.SHOW("SCAN");
  sk.INIT();
  show(sk.C_SCAN(ep));
  sk.SHOW("C_SCAN");
  sk.INIT();
  show(sk.LOOK(ep));
  sk.SHOW("LOOK");
  sk.INIT();
  show(sk.C_LOOK(ep));
  sk.SHOW("C_LOOK");
  return 0;
}
