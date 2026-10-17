#include "scan.h"

#include <chrono>   // high_resolution_clock, duration
#include <ratio>    // std::milli
#include <cstddef>
#include <iostream>
#include <random>
#include <string>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;


int main(int argc, char* argv[])
{
    //std::cout<<"Hello World";
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " n\n";
        return 1;
    }
    
    std::size_t n = static_cast<std::size_t>(std::stoull(argv[1]));
    if (n == 0) {
        std::cerr << "n must be >= 1\n";
        return 1;
    }
    
    // Heap-allocate input and output (n is a runtime value).
    float *arr    = new float[n];
    float *output = new float[n];
    
    // (b) fill arr with random floats in [-1, 1).
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = dist(gen);
    }
    
    // (c) inclusive scan.
    high_resolution_clock::time_point start = high_resolution_clock::now();
    scan(arr, output, n);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, std::milli> ms =
        duration_cast<duration<double, std::milli>>(end - start);
        
    // Print all elements of the scanned array (space-separated, one line).
    // for (std::size_t i = 0; i < n; ++i) {
    //     if (i > 0) std::cout << ' ';
    //     std::cout << output[i];
    // }
    // std::cout << '\n';
    
    // (d) first and last element of the scanned array.
    std::cout << ms.count() << '\n';
    std::cout << output[0] << "\n";
    std::cout << output[n - 1] << "\n";
    
    // (e) release heap memory.
    delete[] arr;
    delete[] output;

    return 0;
}
