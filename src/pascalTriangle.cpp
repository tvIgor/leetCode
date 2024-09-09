#include "tools.h"
#include <memory>

std::vector<std::vector<int>> generate(int numRows) {
  std::vector<std::vector<int>> res{{1}};
  while (--numRows) {
      const auto& prev = res.back();
      res.push_back({1});
      for (int i = 0; i < (prev.size() - 1); ++i)
          ;//res.back().push_back(prev[i] + prev[i+1]);
      res.back().push_back(1);
  }
  return res;
}

std::vector<int> getRow(int rowIndex) {
  std::vector<int> ans(rowIndex + 1, 1);

  for (int i = 2; i < rowIndex + 1; ++i)
    for (int j = 1; j < i; ++j)
      ans[i - j] += ans[i - j - 1];
      

  return ans;
}

LEET_PROBLEM
{
  const auto& res = getRow(4);
}
