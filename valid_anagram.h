#pragma once
#include "tools.h"
#include <unordered_map>

namespace valid_anagram
{
  bool sort_solution(std::vector<int> col1, std::vector<int> col2)
  {
    if (col1.size() != col2.size())
      return false;

    return tools::sort(col1) == tools::sort(col2);
  }

  bool map_solution(std::vector<int> col1, std::vector<int> col2)
  {
    if (col1.size() != col2.size())
      return false;

    std::unordered_map<int, int> dic;
    for (const auto& val : col1) {
      auto found = dic.find(val);
      if (found == dic.end())
        dic[val] = 1;
      else
        found->second++;
    }
    
    for (const auto& val : col2) {
      auto found = dic.find(val);
      if (found == dic.end() || found->second == 0)
        return false;
      
      found->second--;
    }

    return true;
  }

  void run(const std::vector<int>& col1, const std::vector<int>& col2, std::function<bool(std::vector<int>, std::vector<int>)> alg)
  {
      std::cout << "Result: " << alg(col1, col2) << std::endl;
  }

  void run()
  {
    const auto col1 = tools::getArray(1000000, 100);
    auto col2 = tools::getShuffledCopy(col1);
    //col2[col2.size()-1] = 432;

    tools::measureTime("sort_solution", [&](){
        run(col1, col2, sort_solution);
    });

    tools::measureTime("map_solution", [&](){
        run(col1, col2, map_solution);
    });
  }
}