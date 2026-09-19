#pragma once

#include <complex>
#include <vector>

namespace FFT {

// In-place radix-2 Cooley-Tukey. data.size() must be a power of two.
void forward(std::vector<std::complex<float>>& data);

// Convenience: real input -> magnitude in dB, returns size/2 bins.
std::vector<float> magnitudeDb(const std::vector<float>& samples);

}  // namespace FFT