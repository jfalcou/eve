#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <bitset>
#include <immintrin.h>

/**
 * 03_Examples/01_conditional_code - Implementing conditional operations with SIMD
 *
 * This example demonstrates how to implement conditional logic using SIMD:
 * 1. Clamping values to a range
 * 2. Filtering positive values
 * 3. Complex conditional operations (multiple conditions)
 * 4. Using masks and blending for conditional selection
 *
 * Conditional operations are challenging in SIMD because traditional branching
 * (if/else statements) doesn't work well with vector operations. Instead, we use
 * comparison operations to create masks, and then use those masks to select values.
 */

int main() {
 //  {
//     std::cout << "=== Intel SIMD Conditional Operations ===" << std::endl;
//     std::cout << std::endl;

//     // Initialize test data
//     // Allocate aligned memory for better performance
//     float* data1 = aligned_alloc<float>(8);
//     float* data2 = aligned_alloc<float>(8);
//     float* result_scalar = aligned_alloc<float>(8);
//     float* result_simd = aligned_alloc<float>(8);

//     // Initialize data1 with ascending values
//     data1[0] = 5.0f;  data1[1] = 10.0f; data1[2] = 15.0f; data1[3] = 20.0f;
//     data1[4] = 25.0f; data1[5] = 30.0f; data1[6] = 35.0f; data1[7] = 40.0f;

//     // Initialize data2 with mixed positive and negative values
//     data2[0] = -1.0f; data2[1] = 4.0f;  data2[2] = 9.0f;  data2[3] = -16.0f;
//     data2[4] = 25.0f; data2[5] = -36.0f; data2[6] = 49.0f; data2[7] = -64.0f;

//     // Load data into SIMD registers
//     __m256 vector1 = _mm256_load_ps(data1);
//     __m256 vector2 = _mm256_load_ps(data2);

//     // Print input data
//     print_m256(vector1, "Vector 1");
//     print_m256(vector2, "Vector 2");
//     std::cout << std::endl;

//     // --------- 1. Clamping Values -------------
//     std::cout << "1. Clamping Values" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Clamping values in Vector 2 to the range [5, 30]" << std::endl;
//     std::cout << std::endl;

//     // Scalar implementation of clamping
//     auto scalar_clamp = [&]() {
//       for (int i = 0; i < 8; i++) {
//         result_scalar[i] = std::max(5.0f, std::min(30.0f, data2[i]));
//       }
//     };

//     // SIMD implementation of clamping
//     auto simd_clamp = [&]() {
//       __m256 min_val = _mm256_set1_ps(5.0f);
//       __m256 max_val = _mm256_set1_ps(30.0f);

//       // First, clamp to upper bound (min operation)
//       __m256 upper_clamped = _mm256_min_ps(vector2, max_val);

//       // Then, clamp to lower bound (max operation)
//       __m256 result = _mm256_max_ps(upper_clamped, min_val);

//       _mm256_store_ps(result_simd, result);
//     };

//     // Execute both implementations
//     scalar_clamp();
//     simd_clamp();

//     // Print results
//     std::cout << "Scalar clamping result: [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << result_scalar[i] << ", ";
//     }
//     std::cout << result_scalar[7] << "]" << std::endl;

//     std::cout << "SIMD clamping result:   [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << result_simd[i] << ", ";
//     }
//     std::cout << result_simd[7] << "]" << std::endl;

//     // Benchmark comparison
//     benchmark_comparison("Clamping", scalar_clamp, simd_clamp);
//     std::cout << std::endl;

//     // --------- 2. Filtering Positive Values -------------
//     std::cout << "2. Filtering Positive Values" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Creating a mask for positive values in Vector 2" << std::endl;
//     std::cout << std::endl;

//     // Create a mask for positive values
//     __m256 zero = _mm256_setzero_ps();
//     __m256 positive_mask = _mm256_cmp_ps(vector2, zero, _CMP_GT_OQ);

//     // Print the mask (all bits set for true, all bits clear for false)
//     float8 mask_values(positive_mask);
//     std::cout << "Positive mask (as floats): [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << mask_values.a[i] << ", ";
//     }
//     std::cout << mask_values.a[7] << "]" << std::endl;

//     // Convert the mask to a bitmask (one bit per element)
//     int bitmask = _mm256_movemask_ps(positive_mask);
//     std::cout << "Positive mask (as bitmask): " << std::bitset<8>(bitmask) << " (decimal: " << bitmask << ")" << std::endl;

//     // Explain the bitmask
//     std::cout << "Explanation: Positions 1, 2, 4, and 6 have positive values," << std::endl;
//     std::cout << "corresponding to bits 1, 2, 4, and 6 in the bitmask." << std::endl;
//     std::cout << "As a decimal: 2^1 + 2^2 + 2^4 + 2^6 = 2 + 4 + 16 + 64 = 86" << std::endl;
//     std::cout << std::endl;

//     // Scalar implementation of filtering
//     auto scalar_filter = [&]() {
//       for (int i = 0; i < 8; i++) {
//         if (data2[i] > 0) {
//           result_scalar[i] = data2[i];
//         } else {
//           result_scalar[i] = 0.0f;
//         }
//       }
//     };

//     // SIMD implementation of filtering
//     auto simd_filter = [&]() {
//       __m256 mask = _mm256_cmp_ps(vector2, zero, _CMP_GT_OQ);
//       __m256 result = _mm256_and_ps(vector2, mask);  // Keep only positive values
//       _mm256_store_ps(result_simd, result);
//     };

//     // Execute both implementations
//     scalar_filter();
//     simd_filter();

//     // Print results
//     std::cout << "Scalar filtering result: [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << result_scalar[i] << ", ";
//     }
//     std::cout << result_scalar[7] << "]" << std::endl;

//     std::cout << "SIMD filtering result:   [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << result_simd[i] << ", ";
//     }
//     std::cout << result_simd[7] << "]" << std::endl;

//     // Benchmark comparison
//     benchmark_comparison("Filtering", scalar_filter, simd_filter);
//     std::cout << std::endl;

//     // --------- 3. Complex Conditional Operations -------------
//     std::cout << "3. Complex Conditional Operations" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Finding values in Vector 2 that are both positive and greater than Vector 1" << std::endl;
//     std::cout << std::endl;

//     // Create masks for both conditions
//     __m256 positive_mask2 = _mm256_cmp_ps(vector2, zero, _CMP_GT_OQ);
//     __m256 greater_mask = _mm256_cmp_ps(vector2, vector1, _CMP_GT_OQ);

//     // Combine masks with logical AND
//     __m256 combined_mask = _mm256_and_ps(positive_mask2, greater_mask);

//     // Print the combined mask
//     float8 combined_mask_values(combined_mask);
//     std::cout << "Combined mask (as floats): [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << combined_mask_values.a[i] << ", ";
//     }
//     std::cout << combined_mask_values.a[7] << "]" << std::endl;

//     // Convert the combined mask to a bitmask
//     int combined_bitmask = _mm256_movemask_ps(combined_mask);
//     std::cout << "Combined mask (as bitmask): " << std::bitset<8>(combined_bitmask) << " (decimal: " << combined_bitmask << ")" << std::endl;
//     std::cout << std::endl;

//     // Scalar implementation of complex filtering
//     auto scalar_complex = [&]() {
//       for (int i = 0; i < 8; i++) {
//         if (data2[i] > 0 && data2[i] > data1[i]) {
//           result_scalar[i] = data2[i];
//         } else {
//           result_scalar[i] = 0.0f;
//         }
//       }
//     };

//     // SIMD implementation of complex filtering using blendv
//     auto simd_complex = [&]() {
//       __m256 pos_mask = _mm256_cmp_ps(vector2, zero, _CMP_GT_OQ);
//       __m256 gt_mask = _mm256_cmp_ps(vector2, vector1, _CMP_GT_OQ);
//       __m256 combined = _mm256_and_ps(pos_mask, gt_mask);

//       // Use blendv to select values: if mask is true, take from vector2, else take 0
//       __m256 result = _mm256_blendv_ps(zero, vector2, combined);
//       _mm256_store_ps(result_simd, result);
//     };

//     // Execute both implementations
//     scalar_complex();
//     simd_complex();

//     // Print results
//     std::cout << "Scalar complex filtering result: [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << result_scalar[i] << ", ";
//     }
//     std::cout << result_scalar[7] << "]" << std::endl;

//     std::cout << "SIMD complex filtering result:   [";
//     for (int i = 0; i < 7; i++) {
//       std::cout << result_simd[i] << ", ";
//     }
//     std::cout << result_simd[7] << "]" << std::endl;

//     // Benchmark comparison
//     benchmark_comparison("Complex Filtering", scalar_complex, simd_complex);
//     std::cout << std::endl;

//     // --------- 4. Conditional Selection with Blending -------------
//     std::cout << "4. Conditional Selection with Blending" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Using _mm256_blendv_ps for conditional selection" << std::endl;
//     std::cout << std::endl;

//     // Create a new vector with different values
//     __m256 vector3 = _mm256_set_ps(80.0f, 70.0f, 60.0f, 50.0f, 40.0f, 30.0f, 20.0f, 10.0f);
//     print_m256(vector3, "Vector 3");

//     // Create a mask based on a condition (e.g., values > 50)
//     __m256 threshold = _mm256_set1_ps(50.0f);
//     __m256 blend_mask = _mm256_cmp_ps(vector3, threshold, _CMP_GT_OQ);

//     // Use blendv to select values from vector1 or vector2 based on the mask
//     __m256 blended = _mm256_blendv_ps(vector1, vector2, blend_mask);
//     print_m256(blended, "Blended Result (Vector 2 if > 50, else Vector 1)");

//     // Explain the blending operation
//     std::cout << "Explanation: For each element, if Vector 3 > 50, we take the value from Vector 2," << std::endl;
//     std::cout << "otherwise we take the value from Vector 1." << std::endl;
//     std::cout << std::endl;

//     // Clean up
//     free(data1);
//     free(data2);
//     free(result_scalar);
//     free(result_simd);

//   }
  {
    std::cout << "=== EVE SIMD Conditional Operations ===" << std::endl;
    std::cout << std::endl;

    // Initialize test data
    // Allocate aligned memory for better performance
    constexpr size_t N = 8;
    alignas(sizeof(eve::wide<float>)) std::array<float, N> data1{5.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f, 40.0f};
    alignas(sizeof(eve::wide<float>)) std::array<float, N> data2{-1.0f, 4.0f, 9.0f, 16.0, 25.0f, -36.0f, 49.0f, 64.0f};
    alignas(sizeof(eve::wide<float>)) std::array<float, N> result;

    auto print = [](std::string name, auto v){
      std::cout << name << " =  ";

      for(std::size_t i=0; i <  v.size(); ++i)
      {
        std::cout << v[i] << ((i != v.size()-1) ? ", ":"");
      }
      std::cout << std::endl;
    };

    print("data1", data1);
    print("data2", data2);

    // --------- 1. Clamping Values -------------
    std::cout << "1. Clamping Values" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Clamping values in data 2 to the range [5, 30]" << std::endl;
    std::cout << std::endl;

    auto clamp = []( auto & result, auto const& d, auto mi,  auto ma){
      auto clamp_it = [mi, ma](auto e){
        return eve::min(eve::max(e, mi), ma);
        // eve::min and eve::max use the intrinsics of the architecture if they exist or scalar mapping in the other case
        // in fact clamp is implemented in eve :
        // return eve::clamp(e, mi, ma); would to the job
        // mi and/or ma could have been choosen simd values leading to different clamp intervals for each lane.
      };
      // the algo transform_to takes care of using simd chunks
      // the dot function performs dot products on 2n scalars or 2n simd vectors elementwise (see the eve documentation)
      // the input vector size need not be a multiple of (the automagically chosen) best SIMD vector size
      // unroll option is not needed but can tune the performance
       eve::algo::transform_to[eve::algo::unroll<2>](d, result, clamp_it);
    };
    clamp(result, data2, 5.0f, 30.0f);
    print("result", result);

    // --------- 2. Filtering Positive Values -------------
    std::cout << "2. EVE Filtering Positive Values" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Creating a mask for positive values in Vector 2" << std::endl;
    std::cout << std::endl;

    auto filter_pos = []( auto & result, auto const& d){
      auto filter_it = [](auto e){
        return eve::if_else(eve::is_gez(e), e,  eve::zero);
        // eve::if_else acts lanewise using available intrinsics
        // and eve:zero (instead of eve::zero(eve::as(e))) provides access to an optimization
        // eve::is_gez(e) can be  better than e >= 0
      };
      // the algo transform_to takes care of using simd chunks
      // the input vector size need not be a multiple of (the automagically chosen) best SIMD vector size
      eve::algo::transform_to(d, result, filter_it);
    };
    filter_pos(result, data2);
    print("result", result);

    // --------- 3. Complex Conditional Operations -------------
    std::cout << "3. Complex Conditional Operations" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Finding values in Vector 2 that are both positive and greater than Vector 1" << std::endl;
    std::cout << std::endl;

    auto filter_complex = []( auto & result, auto const& d1, auto const& d2){
      auto filter_it = [](auto e){
        auto [e1, e2] = e;
        return eve::if_else(eve::is_gez(e1) && (e2 > e1), e2,  eve::zero);
        // eve::if_else acts lanewise using available intrinsics
        // and eve:zero (instead of eve::zero(eve::as(e))) provides access to an optimization
      };
      // the algo transform_to takes care of using simd chunks
      // the input vector size need not be a multiple of (the automagically chosen) best SIMD vector size
      eve::algo::transform_to(eve::algo::views::zip(d1, d2), result, filter_it);
    };
    filter_complex(result, data1, data2);
    print("data1", data1);
    print("data2", data2);
    print("result", result);

  }
  return 0;
}
