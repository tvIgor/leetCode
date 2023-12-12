
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <thread>
#include "tools.h"

static bool brut_force_solution(std::vector<int>& nums)
{
    for (size_t i = 0; i < nums.size(); i++)
        for (size_t j = i + 1; j < nums.size(); j++)
            if (nums[i] == nums[j])
                return true;

    return false;
}

static bool sort_solution(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());

    for (size_t i = 1; i < nums.size(); i++)
        if (nums[i-1] == nums[i])
            return true;

    return false;
}

static int fncompCallNum = 0;
static bool fncomp(int lhs, int rhs) 
{
    ++fncompCallNum;
    return lhs<rhs;
}

static bool set_solution(std::vector<int>& nums)
{
    std::set<int, bool(*)(int,int)> tmp(fncomp);

    for (const auto& val : nums)
        if (!tmp.insert(val).second)
            return true;

    return false;
}

static bool hash_set_solution(std::vector<int>& nums)
{
    std::unordered_set<int> tmp;

    for (const auto& val : nums)
        if (!tmp.insert(val).second)
            return true;

    return false;
}

static void run(std::vector<int> vec, std::function<bool(std::vector<int>&)> alg)
{
    if (alg(vec))
        std::cout << "true\n";
    else
        std::cout << "false\n";
}

LEET_PROBLEM
{
    tools::measureTime("sort_solution", [](){
        run(tools::getDistinctArray(), sort_solution);
    });

    tools::measureTime("set_solution", [](){
        run(tools::getDistinctArray(), set_solution);
    });
    //std::cout << "fncomp call num = " << fncompCallNum << std::endl;

    tools::measureTime("hash_set_solution", [](){
        run(tools::getDistinctArray(), hash_set_solution);
    });

    /*tools::measureTime("brut_force_solution", [](){
        run(tools::getDistinctArray(), brut_force_solution);
    });*/
}
