#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int search(vector<int> &nums, int target)
  {
    int n = nums.size();
    int i = 0, j = n - 1, mid;
    while (i <= j)
    {
      mid = (i + j) / 2;
      if (nums[mid] == target)
        return mid;
      else if ((nums[mid] <= nums[i] && target > nums[mid] && nums[j] >= target) || (nums[mid] > nums[j] && (target > nums[mid] || target < nums[i])) || (nums[i] <= nums[mid] && nums[j] > nums[mid] && target > nums[mid]))
      {
        i = mid + 1;
      }
      else
      {
        j = mid - 1;
      }
    }
    return -1;
  }
};
int main()
{
//	ListNode *l=new ListNode(0);
//	ListNode *h=l;
//	for(int i=1;i<6;i++)
//	{
//		ListNode *p=new ListNode(i);
//		h->next=p;
//		h=h->next;
//	}
    vector<int> v={4,5,6,7,0,1,2};
	Solution s;
    auto a=s.search(v,7);
    //s.nextPermutation(v);
    cout<<a<<endl;
//    while(a)
//    {
//    	cout<<a->val<<endl;
//    	a=a->next;
//	}
//	for(int i=0;i<v.size();i++)
//      cout<<v[i]<<'\t';
}
