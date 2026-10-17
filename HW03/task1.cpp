#include "matmul.h"

#include <chrono>   // high_resolution_clock, duration
#include <ratio>    // std::milli
#include <cstddef>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <omp.h>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main(int argc, char* argv[]) {
    // ./task1 n t
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " n t\n";
        return 1;
    }
    const std::size_t n = static_cast<std::size_t>(std::stoull(argv[1]));  // matrix dimension
    const int         t = std::stoi(argv[2]);                             // number of threads
    if (n == 0 || t < 1) {
        std::cerr << "n must be >= 1 and t must be >= 1\n";
        return 1;
    }

    // Run the parallel mmul with t threads.
    omp_set_num_threads(t);

    const std::size_t N2 = n * n;
    std::vector<float> A(N2), B(N2), C(N2);

    // Fill A and B with random floats in [-1, 1) (HW02 task3 range).
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (std::size_t k = 0; k < N2; ++k) A[k] = dist(gen);
    for (std::size_t k = 0; k < N2; ++k) B[k] = dist(gen);

    // Time ONLY the mmul call.
    high_resolution_clock::time_point start = high_resolution_clock::now();
    mmul(A.data(), B.data(), C.data(), n);
    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> ms =
        duration_cast<duration<double, std::milli>>(end - start);

    std::cout << C[0]      << "\n";   // first element of C
    std::cout << C[N2 - 1] << "\n";   // last element of C
    std::cout << ms.count() << "\n";  // mmul time in milliseconds

    return 0;
}