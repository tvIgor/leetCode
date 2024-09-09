// LeetCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "tools.h"
#include "testsite.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
        testsite::run();
    else
        tools::getProblem(argv[1]).solve();

    return 0;
}
