#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "tools.h"

namespace move_zeros
{
  void stl_solution(std::vector<int>& nums, int val)
  {
    std::fill(std::remove(nums.begin(), nums.end(), val), nums.end(), val);
  }

  void solution(std::vector<int>& nums, int val)
  {
    auto res = nums.begin();
    auto it = nums.begin();

    while (it != nums.end()) {  
      if (*it != val) {
        if (it != res) *res = *it;
        ++res;
      }
      ++it;
    }

    while (res != nums.end()) {
      *res = val;
      ++res;
    }
  }

  void run(std::vector<int> nums, std::function<void(std::vector<int>&, int)> alg)
  {
      alg(nums, 0);
  }

  void run()
  {      
    
    //auto nums = tools::getArray(100, 20);
    // std::vector<int> nums{9, 0, 9, 2, 0, 0, 1};
    // like_stl_solution(nums, 0);
    // tools::printCollection(nums);

    auto nums = tools::getArray(100000000, 20);
    tools::measureTime("stl_solution", [=](){
        run(nums, stl_solution);
    });

    tools::measureTime("solution", [=](){
        run(nums, solution);
    });
  }
}
