#pragma once

#include <algorithm>
#include <execution>
#include <thread>
#include <cmath>
#include <array>
#include "tools.h"

using namespace std::chrono_literals;

namespace testsite
{
  void test1()
  {
    const auto arr = tools::getArray(90000000);
    auto op = [](int val) { 
      return cbrt(val);
    };

    tools::measureTime("sequenced_policy", [&](){
      std::vector<int> out;
      out.resize(arr.size());
      std::transform(std::execution::seq, arr.begin(), arr.end(), out.begin(), op);
    });

    tools::measureTime("parallel_policy", [&](){
      std::vector<int> out;
      out.resize(arr.size());
      std::transform(std::execution::par, arr.begin(), arr.end(), out.begin(), op);
    });

    tools::measureTime("parallel_unsequenced_policy", [&](){
      std::vector<int> out;
      out.resize(arr.size());
      std::transform(std::execution::par_unseq, arr.begin(), arr.end(), out.begin(), op);
    });
  }

  void run()
  {
  }
}
