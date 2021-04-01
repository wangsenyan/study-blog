/*
 * @lc app=leetcode id=475 lang=cpp
 *
 * [475] Heaters
 */

//思想：按递增排序houses和heaters,求每个房子最近的灯，最近的位置肯定不比上一个最近的靠前
class Solution
{
public:
  int findRadius(vector<int> &houses, vector<int> &heaters)
  {
    sort(heaters.begin(), heaters.end());
    int ans = 0;
    for (auto n : houses)
    {
      int r = lower_bound(heaters.begin(), heaters.end(), n) - heaters.begin();
      int dist_r = r == heaters.size() ? INT_MAX : heaters[r] - n; // right distance
      int dist_l = r > 0 ? n - heaters[r - 1] : INT_MAX;           //left distance
      ans = max(ans, min(dist_l, dist_r));
    }
    return ans;
  }
};
