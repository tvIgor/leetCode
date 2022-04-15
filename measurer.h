#pragma once

#include <chrono>
#include <functional>

class measurer
{
public:
    static void run(const char* opName, std::function<void()> fn)
    {
        const auto t1 = std::chrono::steady_clock::now();
        fn();
        const auto t2 = std::chrono::steady_clock::now();

        const auto timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
        std::cout << opName << " took " << timeSpan << " sec\n";
    }
};
