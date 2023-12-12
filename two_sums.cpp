
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <random>
#include "tools.h"

static std::vector<int> generateArray(int size, int target)
{
    auto res = tools::getDistinctArray(target + 1, size);

    const auto firstIndx = tools::getRandom(res.size());
    auto secondIndx = tools::getRandom(res.size());
    while (firstIndx == secondIndx) 
        secondIndx = tools::getRandom(res.size());

    res.at(firstIndx) = tools::getRandom(target);
    res.at(secondIndx) = target - res.at(firstIndx);

    return res;
}

static std::vector<int> brut_force_solution(std::vector<int>& nums, int target)
{
    for (int i = 0; i < nums.size(); ++i)
        for (int j = i + 1; j < nums.size(); ++j)
            if (nums[i] + nums[j] == target)
                return {i, j};

    return {};
}

static std::vector<int> sort_solution(std::vector<int>& nums, int target)
{
    std::map<int, int> sorted;
    for (int i = 0; i < nums.size(); ++i)
        sorted[nums[i]] = i;

    for (int i = 0; i < nums.size(); ++i) {
        const int otherNum = target - nums[i];
        const auto found = sorted.find(otherNum);
        if (found != sorted.end() && i != found->second)
            return {i, found->second};
    }

    return {};
}

static void run(std::vector<int> vec, int target, std::function<std::vector<int>(std::vector<int>&, int)> alg)
{
    const auto res = alg(vec, target);
    std::cout << "Result: ";

    if (res.size() == 2)
        std::cout << "[" << res.at(0) << ", " << res.at(1) << "]";

    std::cout << " add up to " << target << std::endl;
}

LEET_PROBLEM
{
    constexpr int target = 42;
    const auto tstNums = generateArray(100000, target);

    tools::measureTime("brut_force_solution", [&](){
        run(tstNums, target, brut_force_solution);
    });

    tools::measureTime("sort_solution", [&](){
        run(tstNums, target, sort_solution);
    });
}
