/*
 * @lc app=leetcode id=448 lang=cpp
 *
 * [448] Find All Numbers Disappeared in an Array
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<int> findDisappearedNumbers(vector<int> &nums)
  {
    vector<int> res;
    vector<int> tmp(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++)
    {
      tmp[nums[i] - 1]++;
    }
    for (int i = 0; i < tmp.size(); i++)
    {
      if (tmp[i] == 0)
        res.push_back(i + 1);
    }
    return res;
    //   vector<int> res;
    //   for (int i = 0; i < nums.size(); i++)
    //   {
    //     int index = i;
    //     int tmp;
    //     while (nums[index] != index)
    //     {
    //       cout << index << endl;
    //       tmp = nums[nums[index]];
    //       nums[nums[index]] = index;
    //       index = tmp;
    //     }
    //   }
    //   for (int i = 0; i < nums.size(); i++)
    //   {
    //     if (nums[i] != i)
    //       res.push_back(i);
    //   }
    //   return res;
  }
};
