#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>

#include <array>
#include <iostream>

int main() {
  {
    std::cout << "=== Intel SIMD Header Introduction ===" << std::endl;
    std::cout << "This example demonstrates basic SIMD vector operations." << std::endl;
    std::cout << std::endl;

    // Example 1: Basic vector addition with AVX2
    std::cout << "Example 1: Vector Addition" << std::endl;

    // Initialize two SIMD vectors with 8 float values each
    __m256 a = _mm256_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
    __m256 b = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    // Add the vectors element-wise
    __m256 c = _mm256_add_ps(a, b);

    // Print the vectors using our utility function
    detail::print_m256(a, "Vector A");
    detail::print_m256(b, "Vector B");
    detail::print_m256(c, "A + B");

    // Example 2: Storing SIMD results back to memory
    std::cout << std::endl;
    std::cout << "Example 2: Storing SIMD Results" << std::endl;

    // Allocate aligned memory for results
    float* result = detail::aligned_alloc<float>(8);

    // Store the SIMD vector to memory
    _mm256_store_ps(result, c);

    // Print the results from memory
    std::cout << "Result array: [";
    for (int i = 0; i < 7; i++) {
        std::cout << result[i] << ", ";
    }
    std::cout << result[7] << "]" << std::endl;

    // Example 3: Different data types
    std::cout << std::endl;
    std::cout << "Example 3: Different Data Types" << std::endl;

    // Integer SIMD operations
    __m256i int_a = _mm256_set_epi32(1, 2, 3, 4, 5, 6, 7, 8);
    __m256i int_b = _mm256_set_epi32(8, 7, 6, 5, 4, 3, 2, 1);
    __m256i int_sum = _mm256_add_epi32(int_a, int_b);

    detail::print_m256i(int_a, "Integer Vector A");
    detail::print_m256i(int_b, "Integer Vector B");
    detail::print_m256i(int_sum, "A + B (Integer)");

    // Double precision SIMD operations (4 doubles in a 256-bit register)
    __m256d double_a = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
    __m256d double_b = _mm256_set_pd(4.0, 3.0, 2.0, 1.0);
    __m256d double_sum = _mm256_add_pd(double_a, double_b);

    detail::print_m256d(double_a, "Double Vector A");
    detail::print_m256d(double_b, "Double Vector B");
    detail::print_m256d(double_sum, "A + B (Double)");

    // Clean up
    free(result);

  }
  {
    std::cout << "=== SIMD Header Introduction using EVE ===" << std::endl;
    std::cout << "This example demonstrates basic SIMD vector operations." << std::endl;
    std::cout << std::endl;

    // Example 1: Basic vector addition with any SIMD architecture
    std::cout << "Example 1: Vector Addition" << std::endl;

    // Initialize two SIMD vectors with 8 float values each
    eve::wide a{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    eve::wide b{8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};

    // Add the vectors element-wise
    auto c = eve::add(a, b);

    // Print the vectors using standard iostream
    std::cout <<  "Vector A " << a << std::endl;
    std::cout <<  "Vector B " << b << std::endl;
    std::cout <<  "A+B      " << c << std::endl;

    // Example 2: Storing SIMD results back to memory
    std::cout << std::endl;
    std::cout << "Example 2: Storing SIMD Results" << std::endl;

    // Allocate aligned memory for results
    using T =  decltype(a);
    constexpr auto algt = eve::alignment_v<T>;

//    float* result = aligned_alloc<float>(8);
    alignas(algt) std::array<float, 8> result;

    // Store the SIMD vector to memory
    eve::store(a, eve::as_aligned(&result[0]));

    // Print the results from memory
    std::cout << "Result array: [";
    for (int i = 0; i < 7; i++) {
        std::cout << result[i] << ", ";
    }
    std::cout << result[7] << "]" << std::endl;

    // Example 3: Different data types
    std::cout << std::endl;
    std::cout << "Example 3: Different Data Types" << std::endl;

    // Integer SIMD operations
    eve::wide int_a{1, 2, 3, 4, 5, 6, 7, 8};
    eve::wide int_b{8, 7, 6, 5, 4, 3, 2, 1};
    eve::wide int_c = eve::add(int_a, int_b);

    std::cout <<  "Integer Vector A " << int_a << std::endl;
    std::cout <<  "Integer Vector B " << int_b << std::endl;
    std::cout <<  "Integer A+B      " << int_c << std::endl;
    std::cout << std::endl;

    // Double precision SIMD operations (8 doubles)
    // With sse2 uses four SIMD vectors with 2 double values each
    // With avx2 uses two SIMD vectors with 4 double values each
    // With avx512  uses one SIMD vector with 8 double
    // This is not a problem for EVE
    eve::wide double_a{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    eve::wide double_b{8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    // Add the vectors element-wise
    auto double_c = eve::add(double_a, double_b);

    // Print the vectors using standard iostream
    std::cout <<  "Double Vector A " << double_a << std::endl;
    std::cout <<  "Double Vector B " << double_b << std::endl;
    std::cout <<  "Double A+B      " << double_c << std::endl;
  }
  ////////////////////////////////////////////////////////////
  // EVE advantages
  // all the code is archiecture independant and can cope
  // with intel arm and powerpc and will with risc5
  // simpler code and very large available (simd andscalar compatible) functions panel.
  return 0;
}
