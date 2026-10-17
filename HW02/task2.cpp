#include "convolution.h"

#include <chrono>   // high_resolution_clock, duration
#include <ratio>    // std::milli
#include <cstddef>
#include <iostream>
#include <random>
#include <string>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main(int argc, char* argv[]) {
    // ./task2 n m
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " n m\n";
        return 1;
    }
    std::size_t n = static_cast<std::size_t>(std::stoull(argv[1]));
    std::size_t m = static_cast<std::size_t>(std::stoull(argv[2]));
    if (n == 0 || m == 0) {
        std::cerr << "n and m must be >= 1\n";
        return 1;
    }
    
    if (m % 2 == 0) {
        std::cerr << "m must be odd\n";
        return 1;
    }

    // One generator, two distributions.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> image_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> mask_dist(-1.0f, 1.0f);

    // i) n x n image, row-major, random floats in [-10, 10).
    float *image = new float[n * n];
    for (std::size_t k = 0; k < n * n; ++k) {
        image[k] = image_dist(gen);
    }

    // ii) m x m mask, row-major, random floats in [-1, 1).
    float *mask = new float[m * m];
    for (std::size_t k = 0; k < m * m; ++k) {
        mask[k] = mask_dist(gen);
    }

    float *output = new float[n * n];

    // iii) + iv) apply convolve, timing only that call.
    high_resolution_clock::time_point start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> ms =
        duration_cast<duration<double, std::milli>>(end - start);

    // iv) time in milliseconds.
    std::cout << ms.count() << "\n";
    // v) first element of the convolved array.
    std::cout << output[0] << "\n";
    // vi) last element of the convolved array.
    std::cout << output[n * n - 1] << "\n";

    // vii) deallocate.
    delete[] image;
    delete[] mask;
    delete[] output;
    return 0;
}
