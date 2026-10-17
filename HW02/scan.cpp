#include "scan.h"

// Serial inclusive scan (prefix sum) with the + operator.
// output[i] = arr[0] + arr[1] + ... + arr[i]
void scan(const float *arr, float *output, std::size_t n) {
    float running = 0.0f;
    for (std::size_t i = 0; i < n; ++i) {
        running += arr[i];      // accumulate in index order
        output[i] = running;    // store the inclusive prefix at i
    }
}
