#include "matmul.h"

#include <cstddef>

void mmul1(const double* A, const double* B, double* C, const unsigned int n) {
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            C[static_cast<std::size_t>(i) * n + j] = 0.0;
            for (unsigned int k = 0; k < n; ++k) {
                C[static_cast<std::size_t>(i) * n + j] += A[static_cast<std::size_t>(i) * n + k] * B[static_cast<std::size_t>(k) * n + j];
            }
        }
    }
}

void mmul2(const double* A, const double* B, double* C, const unsigned int n) {
    for (std::size_t idx = 0; idx < static_cast<std::size_t>(n) * n; ++idx) {
        C[idx] = 0.0;
    }
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int k = 0; k < n; ++k) {
            for (unsigned int j = 0; j < n; ++j) {
                C[static_cast<std::size_t>(i) * n + j] += A[static_cast<std::size_t>(i) * n + k] * B[static_cast<std::size_t>(k) * n + j];
            }
        }
    }
}

void mmul3(const double* A, const double* B, double* C, const unsigned int n) {
    for (std::size_t idx = 0; idx < static_cast<std::size_t>(n) * n; ++idx) {
        C[idx] = 0.0;
    }
    for (unsigned int j = 0; j < n; ++j) {
        for (unsigned int k = 0; k < n; ++k) {
            for (unsigned int i = 0; i < n; ++i) {
                C[static_cast<std::size_t>(i) * n + j] += A[static_cast<std::size_t>(i) * n + k] * B[static_cast<std::size_t>(k) * n + j];
            }
        }
    }
}

void mmul4(const std::vector<double>& A, const std::vector<double>& B, double* C, const unsigned int n) {
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            C[static_cast<std::size_t>(i) * n + j] = 0.0;
            for (unsigned int k = 0; k < n; ++k) {
                C[static_cast<std::size_t>(i) * n + j] += A[static_cast<std::size_t>(i) * n + k] * B[static_cast<std::size_t>(k) * n + j];
            }
        }
    }
}
