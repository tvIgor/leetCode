
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "tools.h"

static std::vector<int> brut_force_solution(const std::vector<int>& nums1, const std::vector<int>& nums2)
{
    std::vector<int> res;
    res.reserve(std::max(nums1.size(), nums2.size()));
    
    const std::vector<int>* longest;
    const std::vector<int>* shortest;
    if (nums1.size() < nums2.size()) {
      shortest = &nums1;
      longest = &nums2;
    } else {
      shortest = &nums2;
      longest = &nums1;
    }
    
    std::map<int, int> occur;
    for (const auto& val1 : *longest) {
      int occurTime = -1;
      for (const auto& val2 : *shortest) {
        if (val1 == val2) {
          if (occurTime < 0) occurTime = occur[val1];

          if (occurTime-- == 0) {
            occur[val1]++;
            res.push_back(val1);
            break;
          }
        }
      }
    }

    return res;
}

static std::vector<int> sort_solution(std::vector<int>& nums1, std::vector<int>& nums2)
{
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());

    std::vector<int> res;
    res.reserve(std::max(nums1.size(), nums2.size()));
    size_t i = 0, j = 0;

    while (i < nums1.size() && j < nums2.size()) {
      if (nums1[i] == nums2[j]) {
        res.push_back(nums1[i]);
        i++, j++;
      } else if (nums1[i] < nums2[j]) {
        i++;
      } else {
        j++;
      }
    }

    return res;
}

static std::vector<int> run(std::vector<int> nums1, std::vector<int> nums2, 
std::function<std::vector<int>(std::vector<int>&, std::vector<int>&)> alg)
{
    return alg(nums1, nums2);
}

LEET_PROBLEM
{
    //const auto res =//run({1, 2, 2, 1}, {2, 2}, brut_force_solution);
    //std::cout << "Res: ";
    // for (const auto& num : res) std::cout << num << " ";
    // std::cout << '\n';
    
    const auto nums1 = tools::getArray(10000000);
    const auto nums2 = tools::getArray(100);

    tools::measureTime("sort_solution", [&](){
        run(nums1, nums2, sort_solution);
    });

    tools::measureTime("brut_force_solution", [&](){
        run(nums1, nums2, brut_force_solution);
    });
}
