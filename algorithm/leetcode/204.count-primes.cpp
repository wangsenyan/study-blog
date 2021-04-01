/*
 * @lc app=leetcode id=204 lang=cpp
 *
 * [204] Count Primes
 *
 * https://leetcode.com/problems/count-primes/description/
 *
 * algorithms
 * Easy (28.50%)
 * Total Accepted:    227.5K
 * Total Submissions: 792.7K
 * Testcase Example:  '10'
 *
 * Count the number of prime numbers less than a non-negative number, n.
 * 
 * Example:
 * 
 * 
 * Input: 10
 * Output: 4
 * Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
 * 
 * 
 */
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class Solution
{
public:
  int countPrimes(int n)
  {
    vector<int> seive(n + 1, 1);

    for (int i = 2; i <= sqrt(n); i++)
    {
      if (seive[i] == 1)
      {
        for (int j = i * i; j <= n; j = j + i)
        {
          seive[j] = 0;
        }
      }
    }
    int cnt = 0;
    for (int i = 2; i < n; i++)
      if (seive[i])
        cnt++;
    return cnt;
  }
};
