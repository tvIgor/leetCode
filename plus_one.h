#pragma once

#include <iostream>
#include <vector>
#include "tools.h"

namespace plus_one
{
  void solution(std::vector<int>& digits)
  {
    int i = digits.size();
    
    while (i-- > 0) {
      if (++digits[i] <= 9) return;
      digits[i] = 0;
    }
    
    digits.insert(digits.begin(), 1);
  }

  void run()
  {      
    std::vector<int> digits{8, 9, 9, 9};
    solution(digits);
    tools::printCollection(digits);
  }
}
