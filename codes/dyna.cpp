#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<int> temp_Vec{5, 10, 3, 12, 5, 50, 6}; //A1(30X35), A2(35X15.).....A6(20X25)

//Bottom-up.
pair<vector<vector<int>>, vector<vector<int>>> Matrix_Chain_Order(const vector<int> &temp_Vec)
{
  auto temp_n = temp_Vec.size() - 1;
  vector<vector<int>> temp_VecM, temp_VecS;

  temp_VecM.resize(temp_n + 1);
  temp_VecS.resize(temp_n + 1);

  for (auto &i : temp_VecM)
  {
    i.resize(temp_n + 1);
  }
  for (auto &i : temp_VecS)
  {
    i.resize(temp_n + 1);
  }

  for (auto i = 1; i <= temp_n; ++i)
  {
    temp_VecM[i][i] = 0;
  }

  for (auto l = 2; l <= temp_n; ++l)
  {
    for (auto i = 1; i <= temp_n - l + 1; ++i)
    {
      auto j = i + l - 1;
      temp_VecM[i][j] = INT_MAX;

      for (auto k = i; k <= j - 1; ++k)
      {
        auto temp_q = temp_VecM[i][k] + temp_VecM[k + 1][j] + temp_Vec[i - 1] * temp_Vec[k] * temp_Vec[j];

        if (temp_q < temp_VecM[i][j])
        {
          temp_VecM[i][j] = temp_q;
          temp_VecS[i][j] = k;
        }
      }
    }
  }

  return make_pair(temp_VecM, temp_VecS);
}

//Memoized of part1.
int Lookup_Chain(vector<vector<int>> &temp_VecM, const vector<int> &temp_Vec, const int &i, const int &j)
{
  if (temp_VecM[i][j] < INT_MAX)
  {
    return temp_VecM[i][j];
  }
  if (i == j)
  {
    temp_VecM[i][j] = 0;
  }
  else
  {
    for (auto k = i; k <= j - 1; ++k)
    {
      auto temp_q = Lookup_Chain(temp_VecM, temp_Vec, i, k) + Lookup_Chain(temp_VecM, temp_Vec, k + 1, j) + temp_Vec[i - 1] * temp_Vec[k] * temp_Vec[j];

      if (temp_q < temp_VecM[i][j])
      {
        temp_VecM[i][j] = temp_q;
      }
    }
  }
  return temp_VecM[i][j];
}

//Memoized of part2.
int Memoized_Matrix_Chain(const vector<int> &temp_Vec)
{
  auto temp_n = temp_Vec.size() - 1;
  vector<vector<int>> temp_VecM;

  temp_VecM.resize(temp_n + 1);

  for (auto &i : temp_VecM)
  {
    i.resize(temp_n + 1);
  }

  for (auto &i : temp_VecM)
  {
    for (auto &j : i)
    {
      j = INT_MAX;
    }
  }

  return Lookup_Chain(temp_VecM, temp_Vec, 1, temp_n);
}

//Recusive.
int Recursive_Matrix_Chain(const vector<int> &temp_Vec, const int &i, const int &j)
{
  if (i == j)
  {
    return 0;
  }
  auto temp_n = temp_Vec.size() - 1;
  vector<vector<int>> temp_VecM;

  temp_VecM.resize(temp_n + 1);

  for (auto &x : temp_VecM)
  {
    x.resize(temp_n + 1);
  }

  for (auto &x : temp_VecM)
  {
    for (auto &y : x)
    {
      y = INT_MAX;
    }
  }

  for (auto k = i; k <= j - 1; ++k)
  {
    auto temp_q = Recursive_Matrix_Chain(temp_Vec, i, k) + Recursive_Matrix_Chain(temp_Vec, k + 1, j) + temp_Vec[i - 1] * temp_Vec[k] * temp_Vec[j];

    if (temp_q < temp_VecM[i][j])
    {
      temp_VecM[i][j] = temp_q;
    }
  }

  return temp_VecM[i][j];
}

//Print optimal bracket scheme.
void Print_Optimal_Parens(const vector<vector<int>> &temp_VecS, const int &i, const int &j)
{
  if (i == j)
  {
    cout << "A" << i << " ";
  }
  else
  {
    cout << "("
         << " ";
    Print_Optimal_Parens(temp_VecS, i, temp_VecS[i][j]);
    Print_Optimal_Parens(temp_VecS, temp_VecS[i][j] + 1, j);
    cout << ")"
         << " ";
  }
}

int main()
{
  auto temp_Pair = Matrix_Chain_Order(temp_Vec);
  auto temp_VecM = temp_Pair.first, temp_VecS = temp_Pair.second;

  cout << temp_VecM[2][5] << endl; //A2 to A5 by bottom-up.

  Print_Optimal_Parens(temp_VecS, 2, 5); //A2 to A5 by bottom-up.

  cout << endl
       << endl;
  for (auto &i : temp_VecM)
  { //All of the value.
    for (auto &j : i)
    {
      cout << j << " ";
    }
    cout << endl;
  }

  cout << endl
       << Recursive_Matrix_Chain(temp_Vec, 1, 6) << endl; // A1 to A6 by recursive.

  cout << endl
       << Memoized_Matrix_Chain(temp_Vec) << endl; //A1 to A6 by memoized.

  return 0;
}
