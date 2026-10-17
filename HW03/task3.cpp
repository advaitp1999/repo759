#include "msort.h"

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
    // ./task3 n t ts
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " n t ts\n";
        return 1;
    }
    const std::size_t n  = static_cast<std::size_t>(std::stoull(argv[1]));  // array length
    const int         t  = std::stoi(argv[2]);                             // number of threads
    const std::size_t ts = static_cast<std::size_t>(std::stoull(argv[3])); // threshold
    if (n == 0 || t < 1) {
        std::cerr << "n must be >= 1 and t must be >= 1\n";
        return 1;
    }

    omp_set_num_threads(t);

    // arr of n random ints in [-1000, 1000].
    std::vector<int> arr(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000);
    for (std::size_t k = 0; k < n; ++k) arr[k] = dist(gen);
    // Time ONLY the msort call.
    high_resolution_clock::time_point start = high_resolution_clock::now();
    msort(arr.data(), n, ts);
    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> ms =
        duration_cast<duration<double, std::milli>>(end - start);

    std::cout << arr[0]     << "\n";   // first element of sorted arr
    std::cout << arr[n - 1] << "\n";   // last element of sorted arr
    std::cout << ms.count() << "\n";   // msort time in milliseconds

    return 0;
}
