
#include <iostream>
#include <vector>
#include <numeric>
#include "tools.h"

template <typename T>
int solution(const T& vec)
{
  const size_t fullSum = (vec.size() + 2) * (vec.size() + 1) / 2;
  return std::accumulate(vec.begin(), vec.end(), fullSum, std::minus<size_t>());
}

static int solution_xor(const std::vector<int>& vec)
{
  int fXr{0};
  for (int i = 1; i <= vec.size() + 1; ++i) fXr ^= i;
  const int xr = std::accumulate(vec.begin(), vec.end(), 0, std::bit_xor<int>());
  return xr ^ fXr;
}

LEET_PROBLEM
{      
  std::vector<char> digits{2, 1, 3, 4, 6, 7};
  std::cout << solution(digits) << std::endl;
}
