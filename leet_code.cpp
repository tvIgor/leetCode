// LeetCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "tools.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
        tools::getDefaultProblem().solve();
    else
        tools::getProblem(argv[1]).solve();

    return 0;
}
