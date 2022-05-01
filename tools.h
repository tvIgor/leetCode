#pragma once

#include <vector>
#include <chrono>
#include <functional>
#include <iostream>

namespace tools
{
  inline void measureTime(const char* opName, std::function<void()> fn)
  {
      const auto t1 = std::chrono::steady_clock::now();
      fn();
      const auto t2 = std::chrono::steady_clock::now();

      const auto timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
      std::cout << opName << " took " << timeSpan << " sec\n";
  }

  constexpr int DEFAULT_ARR_SIZE = 1000000;
  std::vector<int> getArray(int size = DEFAULT_ARR_SIZE, int max = INT_MAX);
  std::vector<int> getDistinctArray(int size = DEFAULT_ARR_SIZE);
  
  template<typename T>
  void printCollection(const T& collection) 
  {
    for (const auto& item : collection)
      std::cout << item << ' ';

    std::cout << std::endl;
  }
}
