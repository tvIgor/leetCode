#include "tools.h"
#include <memory>

// 108. Convert sorted array to binary search tree
// Given an integer array nums where the elements are sorted in ascending order, convert it to a 
// height-balanced
// binary search tree.

tools::treeNodePtr getSubTree(const std::vector<int>& nums, int b, int e)
{
  if (b > e) return nullptr;
  const int m = (b + e) / 2;
  auto node = std::make_unique<tools::treeNode>(nums[m]);
  node->left = getSubTree(nums, b, m - 1);
  node->right = getSubTree(nums, m + 1, e);
  return node;
}

LEET_PROBLEM
{
  std::vector<int> nums{-10,-3,0,500,900};
  const auto tree = getSubTree(nums, 0, nums.size() - 1);
  tools::printTree(tree, 3);
}
