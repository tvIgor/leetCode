#include "tools.h"

static void solution(std::vector<int>& digits)
{
  int i = digits.size();
  
  while (i-- > 0) {
    if (++digits[i] <= 9) return;
    digits[i] = 0;
  }
  
  digits.insert(digits.begin(), 1);
}

LEET_PROBLEM
{
  std::vector<int> digits{8, 9, 9, 9};
  solution(digits);
  tools::printCollection(digits);
};
