#ifndef _MinHeap_H_
#define _MinHeap_H_

//insert

//extract-min

//add
using namespace std;
template <typename T>
class MinHeap
{
private:
  vector<T> d;
  int n;

public:
  MinHeap();
  void makeHeap();
  void heap_push(T e);
  T heap_pop();
  T *heap_find(T e);
  void heap_inc()

};

#endif _MinHeap_H_