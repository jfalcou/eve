/**
 * simd_utils.h - Utility functions and macros for SIMD programming
 *
 * This header provides common utilities for SIMD programming, including:
 * - Type definitions for SIMD vectors
 * - Helper macros for alignment
 * - Utility functions for printing SIMD vectors
 * - Performance measurement utilities
 */

#pragma once

#include <immintrin.h> // AVX2, 256-bit operations
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include <functional>

namespace detail
{
// Alignment macros
#define SIMD_ALIGN_32 alignas(32)
#define SIMD_ALIGN_64 alignas(64)

// Helper union for accessing SIMD vector elements
  union float8 {
    __m256 v;
    float a[8];

    float8(__m256 _v) : v(_v) {}
    float8() : v(_mm256_setzero_ps()) {}
  };

  union double4 {
    __m256d v;
    double a[4];

    double4(__m256d _v) : v(_v) {}
    double4() : v(_mm256_setzero_pd()) {}
  };

  union int8 {
    __m256i v;
    int a[8];

    int8(__m256i _v) : v(_v) {}
    int8() : v(_mm256_setzero_si256()) {}
  };

// Print utilities
  inline void print_m256(const __m256& v, const std::string& label = "") {
    float8 tmp(v);
    if (!label.empty()) {
      std::cout << label << ": ";
    }
    std::cout << "[";
    for (int i = 0; i < 7; i++) {
      std::cout << tmp.a[i] << ", ";
    }
    std::cout << tmp.a[7] << "]" << std::endl;
  }

  inline void print_m256d(const __m256d& v, const std::string& label = "") {
    double4 tmp(v);
    if (!label.empty()) {
      std::cout << label << ": ";
    }
    std::cout << "[";
    for (int i = 0; i < 3; i++) {
      std::cout << tmp.a[i] << ", ";
    }
    std::cout << tmp.a[3] << "]" << std::endl;
  }

  inline void print_m256i(const __m256i& v, const std::string& label = "") {
    int8 tmp(v);
    if (!label.empty()) {
      std::cout << label << ": ";
    }
    std::cout << "[";
    for (int i = 0; i < 7; i++) {
      std::cout << tmp.a[i] << ", ";
    }
    std::cout << tmp.a[7] << "]" << std::endl;
  }

// Performance measurement utilities
  class Timer {
  private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string label;

  public:
    Timer(const std::string& _label = "Operation") : label(_label) {
      start_time = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
      auto end_time = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
      std::cout << label << " took " << duration.count() << " microseconds" << std::endl;
    }
  };

// Benchmark function to compare scalar vs SIMD implementations
  template<typename ScalarFunc, typename SimdFunc>
  void benchmark_comparison(
    const std::string& label,
    ScalarFunc scalar_func,
    SimdFunc simd_func,
    int iterations = 1000000
  ) {
    // Warm-up
    scalar_func();
    simd_func();

    // Benchmark scalar implementation
    auto scalar_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
      scalar_func();
    }
    auto scalar_end = std::chrono::high_resolution_clock::now();
    auto scalar_duration = std::chrono::duration_cast<std::chrono::microseconds>(scalar_end - scalar_start);

    // Benchmark SIMD implementation
    auto simd_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
      simd_func();
    }
    auto simd_end = std::chrono::high_resolution_clock::now();
    auto simd_duration = std::chrono::duration_cast<std::chrono::microseconds>(simd_end - simd_start);

    // Print results
    std::cout << "===== " << label << " Benchmark =====" << std::endl;
    std::cout << "First implementation: " << scalar_duration.count() << " microseconds" << std::endl;
    std::cout << "Second implementation: " << simd_duration.count() << " microseconds" << std::endl;

    double speedup = static_cast<double>(scalar_duration.count()) / simd_duration.count();
    std::cout << "Speedup: " << std::fixed << std::setprecision(2) << speedup << "x" << std::endl;
    std::cout << "===============================" << std::endl;
  }

// Allocate aligned memory
  template<typename T>
  T* aligned_alloc(size_t size, size_t alignment = 32) {
    void* ptr = nullptr;
    if (posix_memalign(&ptr, alignment, size * sizeof(T)) != 0) {
      throw std::bad_alloc();
    }
    return static_cast<T*>(ptr);
  }
}
