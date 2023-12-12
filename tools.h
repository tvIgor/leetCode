#pragma once

#include <vector>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>

namespace tools
{
  enum class color {
    black = 30,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
  };

  template<typename T>
  std::string make(const T& val, color c)
  {
    std::ostringstream ss;
    ss << "\u001b[" << static_cast<int>(c) << ";1m" << val << "\u001b[0m";
    return ss.str();
  }

  template<typename T>
  std::string red(const T& val) { return make(val, color::red); };

  template<typename T>
  std::string yellow(const T& val) { return make(val, color::yellow); };

  inline void solution(const char* name, std::function<void()> fn)
  {
    fn();
  }

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
  void printCollection(const T& collection, color c) 
  {
    for (const auto& item : collection)
      std::cout << "\u001b[" << static_cast<int>(c) << ";1m" << item << "\u001b[0m" << ' ';

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

  class problem
  {
    public:
      explicit problem(const char* name);
      virtual ~problem() = default;

      void solve() const;

    protected:
      virtual void body() const = 0;
  };

  const problem& getProblem(const std::string& name);
  std::vector<std::string> getProblems();
}

#define LEET_PROBLEM namespace { class p_impl final : public tools::problem {\
  public:\
    explicit p_impl(const char* name) : tools::problem(name) {}\
  protected:\
    virtual void body() const override;\
} pObj(__FILE__);}\
\
void p_impl::body() const
