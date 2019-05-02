/*
 * @lc app=leetcode id=575 lang=cpp
 *
 * [575] Distribute Candies
 */
class Solution
{
public:
  int distributeCandies(vector<int> &candies)
  {
    sort(candies.begin(), candies.end());
    int count = 1;
    for (int i = 1; i < candies.size() && count < candies.size() / 2; ++i)
      count += candies[i] != candies[i - 1];
    return count;
  }
};
