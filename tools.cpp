#include "tools.h"
#include <chrono>
#include <algorithm>
#include <numeric>
#include <random>

void ass() { std::cout << "ass\n"; }

namespace tools
{
  std::vector<int> getArray(int size)
  {
    std::vector<int> vec(size);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::generate(vec.begin(), vec.end(), generator);
    return vec;
  }

  std::vector<int> getDistinctArray(int size)
  {
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 0);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
    return vec;
  }
}