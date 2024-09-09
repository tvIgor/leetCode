#pragma once

#include <vector>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <memory>

namespace tools
{
  struct treeNode {
    int val;
    std::unique_ptr<treeNode> left;
    std::unique_ptr<treeNode> right;
    treeNode() : val(0), left(nullptr), right(nullptr) {}
    treeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  };
  using treeNodePtr = std::unique_ptr<treeNode>;

  void printTree(const treeNodePtr& tree, int itemWidth = 2);

  struct listNode {
    int val{0};
    listNode* next{nullptr};
    listNode() : val(0) {}
    listNode(int v) : val(v) {}
    listNode(int v, listNode* n) : val(v), next(n) {}
  };

  listNode* generateList(int size);
  void deleteList(listNode* list);
  void printList(const listNode* list);

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
  std::string magenta(const T& val) { return make(val, color::magenta); };

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

      virtual bool isDefault() const = 0;
      void solve() const;

    protected:
      virtual void body() const = 0;

    private:
      const std::string _name;
  };

  const problem& getProblem(const std::string& name);
  const problem& getDefaultProblem();
  std::vector<std::string> getProblems();
}

#define LEET_PROBLEM namespace { class p_impl final : public tools::problem {\
  public:\
    explicit p_impl(const char* name) : tools::problem(name) {}\
  protected:\
    virtual bool isDefault() const override { return false; }\
    virtual void body() const override;\
} pObj(__FILE__);}\
\
void p_impl::body() const

#define DEFAULT_LEET_PROBLEM namespace { class p_impl final : public tools::problem {\
  public:\
    explicit p_impl(const char* name) : tools::problem(name) {}\
  protected:\
    virtual bool isDefault() const override { return true; }\
    virtual void body() const override;\
} pObj(__FILE__);}\
\
void p_impl::body() const
