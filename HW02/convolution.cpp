#include "convolution.h"
 
#include <cstddef>   // std::size_t, std::ptrdiff_t
 
// g[x,y] = sum_{i,j} mask[i,j] * f[x + i - (m-1)/2, y + j - (m-1)/2]
// Boundary rule (indices r,c into the image):
//   both r,c in [0, n-1]      -> real image value
//   exactly one of r,c out    -> 1
//   both r,c out              -> 0
void convolve(const float *image, float *output, std::size_t n,
              const float *mask, std::size_t m) {
    const std::ptrdiff_t N    = static_cast<std::ptrdiff_t>(n);
    const std::ptrdiff_t half = static_cast<std::ptrdiff_t>((m - 1) / 2);
 
    for (std::size_t x = 0; x < n; ++x) {
        for (std::size_t y = 0; y < n; ++y) {
            float sum = 0.0f;
            for (std::size_t i = 0; i < m; ++i) {
                for (std::size_t j = 0; j < m; ++j) {
                    // Image coordinates this mask tap reads. Computed in SIGNED
                    // arithmetic: x + i - half can be negative.
                    const std::ptrdiff_t r =
                        static_cast<std::ptrdiff_t>(x) + static_cast<std::ptrdiff_t>(i) - half;
                    const std::ptrdiff_t c =
                        static_cast<std::ptrdiff_t>(y) + static_cast<std::ptrdiff_t>(j) - half;
 
                    const bool r_in = (r >= 0 && r < N);
                    const bool c_in = (c >= 0 && c < N);
 
                    float f;
                    if (r_in && c_in) {
                        f = image[static_cast<std::size_t>(r) * n +
                                  static_cast<std::size_t>(c)];
                    } else if (r_in || c_in) {
                        f = 1.0f;   // exactly one coordinate out of bounds
                    } else {
                        f = 0.0f;   // both coordinates out of bounds
                    }
 
                    sum += mask[i * m + j] * f;
                }
            }
            output[x * n + y] = sum;
        }
    }
}
