#include "fft.h"

#include <algorithm>
#include <cmath>

namespace FFT {

namespace {
constexpr float kPi = 3.14159265358979323846f;
}

void forward(std::vector<std::complex<float>>& data)
{
    const size_t n = data.size();
    if (n <= 1)
        return;

    // --- bit-reversal permutation ---
    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            std::swap(data[i], data[j]);
    }

    // --- butterfly stages ---
    for (size_t len = 2; len <= n; len <<= 1) {
        const float angle = -2.0f * kPi / static_cast<float>(len);
        const std::complex<float> wlen(std::cos(angle), std::sin(angle));

        for (size_t i = 0; i < n; i += len) {
            std::complex<float> w(1.0f, 0.0f);

            for (size_t k = 0; k < len / 2; ++k) {
                const std::complex<float> u = data[i + k];
                const std::complex<float> v = data[i + k + len / 2] * w;

                data[i + k]             = u + v;
                data[i + k + len / 2]   = u - v;

                w *= wlen;
            }
        }
    }
}

std::vector<float> magnitudeDb(const std::vector<float>& samples)
{
    const size_t n = samples.size();

    std::vector<std::complex<float>> buf(n);

    // Hann window, applied on the way in
    for (size_t i = 0; i < n; ++i) {
        const float w = 0.5f * (1.0f - std::cos(2.0f * kPi * static_cast<float>(i)
                                                / static_cast<float>(n - 1)));
        buf[i] = std::complex<float>(samples[i] * w, 0.0f);
    }

    forward(buf);

    std::vector<float> out(n / 2);
    const float norm = 2.0f / static_cast<float>(n);

    for (size_t k = 0; k < n / 2; ++k) {
        const float mag = std::abs(buf[k]) * norm;
        out[k] = 20.0f * std::log10(std::max(mag, 1e-6f));
    }

    return out;
}

}  // namespace FFT