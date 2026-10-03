#include "matmul.h"

#include <chrono>   // high_resolution_clock, duration
#include <ratio>    // std::milli
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main() {
    const unsigned int n = 1024;
    const std::size_t  N2 = static_cast<std::size_t>(n) * n;

    // A, B, C stored row-major in 1D vectors. Passing .data() satisfies the
    // raw-pointer signatures (mmul1-3); passing the vectors satisfies mmul4.
    std::vector<double> A(N2), B(N2), C(N2);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    for (std::size_t k = 0; k < N2; ++k) A[k] = dist(gen);
    for (std::size_t k = 0; k < N2; ++k) B[k] = dist(gen);

    std::cout << n << "\n";                             // number of rows

    high_resolution_clock::time_point start, end;
    duration<double, std::milli> ms;

    // mmul1
    start = high_resolution_clock::now();
    mmul1(A.data(), B.data(), C.data(), n);
    end = high_resolution_clock::now();
    ms = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << ms.count() << "\n" << C[N2 - 1] << "\n";

    // mmul2
    start = high_resolution_clock::now();
    mmul2(A.data(), B.data(), C.data(), n);
    end = high_resolution_clock::now();
    ms = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << ms.count() << "\n" << C[N2 - 1] << "\n";

    // mmul3
    start = high_resolution_clock::now();
    mmul3(A.data(), B.data(), C.data(), n);
    end = high_resolution_clock::now();
    ms = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << ms.count() << "\n" << C[N2 - 1] << "\n";

    // mmul4
    start = high_resolution_clock::now();
    mmul4(A, B, C.data(), n);
    end = high_resolution_clock::now();
    ms = duration_cast<duration<double, std::milli>>(end - start);
    std::cout << ms.count() << "\n" << C[N2 - 1] << "\n";

    return 0;
}
