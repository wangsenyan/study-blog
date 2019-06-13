#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#define N 20
#define M 4

std::queue<int> q;
std::vector<int> f(M, -1);
int fifo(std::vector<int> arr);
void show(std::vector<int> a);
int lru(std::vector<int> arr);
int opt(std::vector<int> arr);
int main(int argc, char *agrv[])
{
  srand((unsigned)time(NULL));
  std::vector<int> arr;
  for (int i = 0; i < N; i++)
    arr.push_back(rand() % 10);
  show(arr);
  std::cout << opt(arr) << std::endl;
}
//FIFO
int fifo(std::vector<int> arr)
{
  int num = 0;
  for (int i = 0, j = 0; i < N; i++)
  {
    int k = 0;
    for (; k < M; k++)
    {
      if (arr[i] == f[k % M] || f[k % M] == -1)
        break;
    }
    if (f[k % M] == -1)
    {
      j = k % M;
      f[j] = arr[i];
      q.push(k % M);
      num++;
    }
    else if (k == M)
    {
      j = q.front();
      f[j] = arr[i];
      q.pop();
      q.push(j);
      num++;
    }
  }
  return num;
}

//LRU,使用最小堆
int lru(std::vector<int> arr)
{
  int num = 0;
  std::vector<int> t(M, 0); //调用次数
  for (int i = 0; i < N; i++)
  {
    int k = 0;
    for (; k < M; k++)
    {
      if (arr[i] == f[k] || f[k] == -1)
        break;
    }
    if (f[k] == -1) //
    {
      f[k] = arr[i];
      t[k]++;
      num++;
    }
    else if (k == M) //缺页换帧
    {
      //寻找最近最少使用的
      int m = 0;
      for (int j = 1; j < M; j++)
      {
        if (t[m] > t[j])
          m = j;
      }
      f[m] = arr[i];
      t[m] = 1;
      num++;
    }
    else
      t[k]++;
    show(f);
    show(t);
  }
  return num;
}
//最优
int opt(std::vector<int> arr)
{
  int num = 0;
  for (int i = 0; i < N; i++)
  {
    int k = 0;
    for (; k < M; k++)
    {
      if (arr[i] == f[k] || f[k] == -1)
        break;
    }
    if (f[k] == -1)
    {
      f[k] = arr[i];
      num++;
    }
    else if (k == M) //缺页
    {
      int m = 0, s = i + 1;
      for (int j = 0; j < M; j++)
      {
      	int l = i + 1;
        for (; l < N; l++)
        {
          if (f[j] == arr[l])
          {
            m = s < l ? j : m;
            s = s < l ? l : s;
            //std::cout<<s<<" "<<m<<std::endl;
            break;
          }
          m=j;
        }
        if(l==N)
          break;
      }
      f[m] = arr[i];
      num++;
    }
    show(f);
  }
  return num;
}
void show(std::vector<int> a)
{
  for (auto e : a)
    std::cout << e << '\t';
  std::cout << std::endl;
}
