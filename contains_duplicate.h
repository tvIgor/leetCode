#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <thread>
#include "measurer.h"

namespace contains_duplicate
{
    constexpr int ARRAY_SIZE = 2000000;

    bool brut_force_solution(std::vector<int>& nums)
    {
        for (size_t i = 0; i < nums.size(); i++)
            for (size_t j = i + 1; j < nums.size(); j++)
                if (nums[i] == nums[j])
                    return true;

        return false;
    }

    bool sort_solution(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        for (size_t i = 1; i < nums.size(); i++)
            if (nums[i-1] == nums[i])
                return true;

        return false;
    }

    static int fncompCallNum = 0;
    bool fncomp(int lhs, int rhs) 
    {
        ++fncompCallNum;
        return lhs<rhs;
    }

    bool set_solution(std::vector<int>& nums)
    {
        std::set<int, bool(*)(int,int)> tmp(fncomp);

        for (const auto& val : nums)
            if (!tmp.insert(val).second)
                return true;

        return false;
    }

    bool hash_set_solution(std::vector<int>& nums)
    {
        std::unordered_set<int> tmp;

        for (const auto& val : nums)
            if (!tmp.insert(val).second)
                return true;

        return false;
    }

    std::vector<int> getDistinctNums()
    {
        std::set<int> uniqueInts;
        std::vector<int> vec(ARRAY_SIZE);
        std::iota(vec.begin(), vec.end(), 0);
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
        
        return vec;
    }

    void run(std::vector<int> vec, std::function<bool(std::vector<int>&)> alg)
    {
        if (alg(vec))
            std::cout << "true\n";
        else
            std::cout << "false\n";
    }

    void run()
    {
        measurer::run("sort_solution", [](){
            run(getDistinctNums(), sort_solution);
        });

        measurer::run("set_solution", [](){
            run(getDistinctNums(), set_solution);
        });
        //std::cout << "fncomp call num = " << fncompCallNum << std::endl;

        measurer::run("hash_set_solution", [](){
            run(getDistinctNums(), hash_set_solution);
        });

        /*measurer::run("brut_force_solution", [](){
            run(getDistinctNums(), brut_force_solution);
        });*/
    }
}
