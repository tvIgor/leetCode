#include "tools.h"
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <ranges>
#include <queue>
#include <math.h>

using problem_map = std::unordered_map<std::string, const tools::problem*>;

namespace tools
{
  static int getHeight(const treeNodePtr& tree)
  {
    if (nullptr == tree)
      return 0;

    const int lHeight = getHeight(tree->left) + 1;
    const int rHeight = getHeight(tree->right) + 1;

    return (lHeight > rHeight) ? lHeight : rHeight;
  }

  static void bfs(const treeNodePtr& tree, std::function<void(int, const treeNodePtr& node)> fn)
  {
    if (!tree || !fn) return;

    int lvl{1};
    int lastLvl{1};
    std::queue<std::pair<int, const treeNodePtr&>> q;
    q.push({1, tree});

    while (!q.empty() && q.front().first <= lastLvl) {
      auto item = q.front();
      q.pop();
      fn(item.first, item.second);
      if (item.second) {
        q.push({item.first + 1, item.second->left});
        q.push({item.first + 1, item.second->right});
        if (item.second->left || item.second->right)
          lastLvl = item.first + 1;
      }
    }
  }

  void printTree(const treeNodePtr& tree, int itemWidth)
  {
    constexpr char filler = ' ';
    int treeHeight = getHeight(tree) + 1;
    int currentLvl = 0;

    bfs(tree, [&](int lvl, const treeNodePtr& node) {
      if (lvl != currentLvl) {
        if (currentLvl)
          std::cout << "\n";

        currentLvl = lvl;
        treeHeight--;

        const int gap = (std::pow(2, treeHeight - 1) - 1) * itemWidth;
        std::cout << std::setfill(filler) << std::setw(gap) << "";
      } else {
        const int gap = (std::pow(2, treeHeight) - 1) * itemWidth;
        std::cout << std::setfill(filler) << std::setw(gap) << "";
      }

      if (node) {
        std::cout.width(itemWidth);
        std::cout << std::to_string(node->val);
      } else {
        std::cout << std::setfill(filler) << std::setw(itemWidth) << "";
      }
    });
  }

  listNode* generateList(int size)
  {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    listNode* begin;
    listNode* last{nullptr};

    while (size--) {
      auto el = new listNode(generator() % 100);
      if (last) {
        last->next = el;
        last = last->next;
      } else {
        begin = el;
        last = begin;
      }
    }
    return begin;
  }

  void deleteList(listNode* list)
  {
    while (list) {
      auto current = list;
      list = list->next;
      delete current;
    }
  }

  void printList(const listNode* list)
  {
    while (list) {
      std::cout << list->val << " ";
      list = list->next;
    }
    std::cout << "\n";
  }

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

  problem::problem(const char* name) :
  _name(std::filesystem::path(name).stem().string())
  {
    getProblemMap()[_name] = this;
  }

  void problem::solve() const
  {
    std::cout 
      << magenta("Problem: ")
      << magenta(_name)
      << "\n";
      
    body();
  }

  const problem& getProblem(const std::string& name)
  {
    auto found = getProblemMap().find(name);
    
    if (found == getProblemMap().end())
      throw std::runtime_error("Problem is not found");
    
    return *found->second;
  }

  const problem& getDefaultProblem()
  {
    auto& mmm = getProblemMap();
    const auto defaultNum = std::ranges::count_if(mmm, [](const auto& pair){ return pair.second->isDefault(); });
    if (defaultNum == 0)
      throw std::runtime_error("There are no default problem.");

    if (defaultNum > 1)
      throw std::runtime_error("There are more than one default problems.");

    auto found = std::ranges::find_if(mmm, [](const auto& pair){ return pair.second->isDefault(); });
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
