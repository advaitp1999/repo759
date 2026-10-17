#include "msort.h"

#include <cstddef>
#include <vector>

// Merges two sorted subarrays arr[left..mid] and arr[mid+1..right].
// (Same logic as the reference merge, adapted to a raw int* and size_t indices.)
static void merge(int* arr, std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t n1 = mid - left + 1;
    std::size_t n2 = right - mid;

    std::vector<int> L(arr + left,      arr + mid + 1);   // copy of left half
    std::vector<int> R(arr + mid + 1,   arr + right + 1); // copy of right half

    std::size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];   // <= keeps the sort stable
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Serial merge sort, used once a subarray drops below the threshold.
static void mergeSortSerial(int* arr, std::size_t left, std::size_t right) {
    if (left >= right) return;
    std::size_t mid = left + (right - left) / 2;
    mergeSortSerial(arr, left, mid);
mergeSortSerial(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Parallel merge sort: spawn each half as an OpenMP task while the subarray
// is large; below the threshold, sort serially to avoid task overhead.
static void mergeSortParallel(int* arr, std::size_t left, std::size_t right,
                              std::size_t threshold) {
    if (left >= right) return;

    std::size_t size = right - left + 1;
    if (size < threshold) {
        mergeSortSerial(arr, left, right);   // serial cutoff
        return;
    }

    std::size_t mid = left + (right - left) / 2;

    // left/mid/right/threshold are firstprivate by default in a task,
    // so each task gets its own copy of the indices; arr is the shared array.
    #pragma omp task shared(arr)
    mergeSortParallel(arr, left, mid, threshold);
    #pragma omp task shared(arr)
    mergeSortParallel(arr, mid + 1, right, threshold);
    #pragma omp taskwait          // both halves done before merging

    merge(arr, left, mid, right);
}

// Public entry point. Opens one parallel region; a single thread kicks off
// the recursion and the whole team picks up the spawned tasks.
void msort(int* arr, const std::size_t n, const std::size_t threshold) {
    if (n <= 1) return;           // nothing to sort
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortParallel(arr, 0, n - 1, threshold);
    }
}
