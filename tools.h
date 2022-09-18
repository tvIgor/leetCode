#pragma once

#include <vector>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>

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

  int getRandom(int max = INT_MAX);

  constexpr int DEFAULT_ARR_SIZE = 1000000;
  std::vector<int> getArray(int size = DEFAULT_ARR_SIZE, int max = INT_MAX);
  std::vector<int> getDistinctArray(int minValue = 0, int size = DEFAULT_ARR_SIZE);
  
  template<typename T>
  void printCollection(const T& collection) 
  {
    for (const auto& item : collection)
      std::cout << item << ' ';

    std::cout << std::endl;
  }

  template<typename T>
  T& shuffle(T& collection)
  {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(collection.begin(), collection.end(), std::default_random_engine(seed));
    return collection;
  }

  template<typename T>
  T getShuffledCopy(const T& collection)
  {
    T ret{collection};
    return shuffle(ret);
  }

  template<typename T>
  T& sort(T& collection)
  {
    std::sort(collection.begin(), collection.end());
    return collection;
  }
}
