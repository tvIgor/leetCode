#include "tools.h"
#include <chrono>
#include <algorithm>
#include <numeric>

namespace tools
{
  int getRandom(int max)
  {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    return generator() % max;
  }

  std::vector<int> getArray(int size, int max)
  {
    std::vector<int> vec(size);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::generate(vec.begin(), vec.end(), [&](){ return generator() % max; });
    return vec;
  }

  std::vector<int> getDistinctArray(int minValue, int size)
  {
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), minValue);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();  
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
    return vec;
  }
}