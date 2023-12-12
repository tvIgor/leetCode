#include "tools.h"
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <ranges>

using problem_map = std::unordered_map<std::string, const tools::problem*>;

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

  static problem_map& getProblemMap()
  {
    static problem_map pMap;
    return pMap;
  }

  problem::problem(const char* name)
  {
    const auto& fileName = std::filesystem::path(name).stem().string();
    getProblemMap()[fileName] = this;
  }

  void problem::solve() const
  {
    body();
  }

  const problem& getProblem(const std::string& name)
  {
    auto found = getProblemMap().find(name);
    
    if (found == getProblemMap().end())
      throw std::runtime_error("Problem is not found");
    
    return *found->second;
  }

  std::vector<std::string> getProblems()
  {
    std::vector<std::string> res;
    res.reserve(getProblemMap().size());
    std::ranges::transform(getProblemMap(), std::back_inserter(res), [](const auto& pair) { return pair.first; });
    return res;
  }
}