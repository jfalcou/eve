#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <memory>

/**
 * 01_Basics/04_loading_data - Loading and storing SIMD data
 * 
 * This example demonstrates different ways to load data into SIMD vectors:
 * 1. Aligned load (_mm256_load_ps) - Requires 32-byte aligned memory
 * 2. Unaligned load (_mm256_loadu_ps) - Works with any memory address
 * 3. Masked load (_mm256_maskload_ps) - Selectively loads elements based on a mask
 * 4. Stream load (_mm256_stream_load_si256) - Non-temporal load that bypasses cache
 * 
 * And different ways to store SIMD data:
 * 1. Aligned store (_mm256_store_ps) - Requires 32-byte aligned memory
 * 2. Unaligned store (_mm256_storeu_ps) - Works with any memory address
 * 3. Masked store (_mm256_maskstore_ps) - Selectively stores elements based on a mask
 * 4. Stream store (_mm256_stream_ps) - Non-temporal store that bypasses cache
 * 
 * We'll also compare the performance of these methods.
 */

constexpr int ARRAY_SIZE = 8;
int main() {
  {
    const int TEST_ITERATIONS = 10000000;
    std::cout << "=== Intel SIMD Data Loading and Storing ===" << std::endl;
    std::cout << std::endl;

    // --------- 1. Aligned vs. Unaligned Load -------------
    std::cout << "1. Aligned vs. Unaligned Load" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Comparing aligned and unaligned memory access." << std::endl;
    std::cout << std::endl;
    
    // Allocate aligned and unaligned memory
    float* aligned_data = detail::aligned_alloc<float>(ARRAY_SIZE, 32);  // 32-byte alignment for AVX
    float* unaligned_data = new float[ARRAY_SIZE + 1];  // +1 to ensure we can create unaligned pointer
    float* unaligned_ptr = unaligned_data + 1;  // Offset by 1 to ensure unalignment
    
    // Initialize data
    for (int i = 0; i < ARRAY_SIZE; i++) {
        aligned_data[i] = static_cast<float>(i + 1);
        unaligned_ptr[i] = static_cast<float>(i + 1);
    }
    
    // Demonstrate aligned load
    __m256 aligned_vec = _mm256_load_ps(aligned_data);
    print_m256(aligned_vec, "Aligned load result");
    
    // Demonstrate unaligned load
    __m256 unaligned_vec = _mm256_loadu_ps(unaligned_ptr);
    print_m256(unaligned_vec, "Unaligned load result");
    
    // Performance comparison
    Timer timer("Aligned vs. Unaligned Load Performance");
    
    // Benchmark aligned load
    auto aligned_load = [&]() {
        __m256 result;
        for (int i = 0; i < TEST_ITERATIONS; i++) {
            result = _mm256_load_ps(aligned_data);
        }
        return result;
    };
    
    // Benchmark unaligned load
    auto unaligned_load = [&]() {
        __m256 result;
        for (int i = 0; i < TEST_ITERATIONS; i++) {
            result = _mm256_loadu_ps(unaligned_ptr);
        }
        return result;
    };
    
    benchmark_comparison("Load Operations", aligned_load, unaligned_load, 10);
    std::cout << std::endl;

    // --------- 2. Masked Load -------------
    std::cout << "2. Masked Load" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Selectively loading elements based on a mask." << std::endl;
    std::cout << std::endl;
    
    // Create a mask to load only elements 0, 2, 4, and 6
    __m256i mask = _mm256_set_epi32(0, -1, 0, -1, 0, -1, 0, -1);
    
    // Perform masked load (elements not selected by mask will be zero)
    __m256 masked_vec = _mm256_maskload_ps(aligned_data, mask);
    print_m256(masked_vec, "Masked load result (even indices only)");
    std::cout << std::endl;

    // --------- 3. Aligned vs. Unaligned Store -------------
    std::cout << "3. Aligned vs. Unaligned Store" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Comparing aligned and unaligned store operations." << std::endl;
    std::cout << std::endl;
    
    // Create a test vector
    __m256 test_vec = _mm256_set_ps(16.0f, 14.0f, 12.0f, 10.0f, 8.0f, 6.0f, 4.0f, 2.0f);
    
    // Perform aligned store
    _mm256_store_ps(aligned_data, test_vec);
    
    std::cout << "Aligned store result: [";
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        std::cout << aligned_data[i] << ", ";
    }
    std::cout << aligned_data[ARRAY_SIZE - 1] << "]" << std::endl;
    
    // Perform unaligned store
    _mm256_storeu_ps(unaligned_ptr, test_vec);
    
    std::cout << "Unaligned store result: [";
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        std::cout << unaligned_ptr[i] << ", ";
    }
    std::cout << unaligned_ptr[ARRAY_SIZE - 1] << "]" << std::endl;
    
    // Performance comparison
    Timer timer2("Aligned vs. Unaligned Store Performance");
    
    // Benchmark aligned store
    auto aligned_store = [&]() {
        for (int i = 0; i < TEST_ITERATIONS; i++) {
            _mm256_store_ps(aligned_data, test_vec);
        }
    };
    
    // Benchmark unaligned store
    auto unaligned_store = [&]() {
        for (int i = 0; i < TEST_ITERATIONS; i++) {
            _mm256_storeu_ps(unaligned_ptr, test_vec);
        }
    };
    
    benchmark_comparison("Store Operations", aligned_store, unaligned_store, 10);
    std::cout << std::endl;

    // --------- 4. Masked Store -------------
    std::cout << "4. Masked Store" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Selectively storing elements based on a mask." << std::endl;
    std::cout << std::endl;
    
    // Reset aligned data
    for (int i = 0; i < ARRAY_SIZE; i++) {
        aligned_data[i] = 0.0f;
    }
    
    // Create a mask to store only elements 1, 3, 5, and 7
    __m256i mask2 = _mm256_set_epi32(-1, 0, -1, 0, -1, 0, -1, 0);
    
    // Perform masked store
    _mm256_maskstore_ps(aligned_data, mask2, test_vec);
    
    std::cout << "Masked store result (odd indices only): [";
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        std::cout << aligned_data[i] << ", ";
    }
    std::cout << aligned_data[ARRAY_SIZE - 1] << "]" << std::endl;
    std::cout << std::endl;

    // --------- 5. Stream Load/Store (Non-temporal) -------------
    std::cout << "5. Stream Load/Store (Non-temporal)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using non-temporal loads and stores that bypass the cache." << std::endl;
    std::cout << "Useful for large data sets that won't be reused soon." << std::endl;
    std::cout << std::endl;
    
    // Allocate a large array to demonstrate streaming operations
    const int LARGE_SIZE = 1024;
    float* large_array = aligned_alloc<float>(LARGE_SIZE, 32);
    
    // Initialize the array
    for (int i = 0; i < LARGE_SIZE; i++) {
        large_array[i] = static_cast<float>(i);
    }
    
    // Perform stream load and store
    for (int i = 0; i < LARGE_SIZE; i += 8) {
        // Stream load (using _mm256_stream_load_si256 which requires casting)
        __m256 loaded = _mm256_loadu_ps(&large_array[i]);
        
        // Process the data (simple multiplication by 2)
        __m256 processed = _mm256_mul_ps(loaded, _mm256_set1_ps(2.0f));
        
        // Stream store (non-temporal store that bypasses cache)
        _mm256_stream_ps(&large_array[i], processed);
    }
    
    // Ensure all streaming stores are visible
    _mm_sfence();
    
    // Print a small section of the result
    std::cout << "Stream store result (first 16 elements): [";
    for (int i = 0; i < 15; i++) {
        std::cout << large_array[i] << ", ";
    }
    std::cout << large_array[15] << "]" << std::endl;
    
    // Clean up
    free(aligned_data);
    delete[] unaligned_data;
    free(large_array);
  }
  {
    
  }
  return 0;
}

  ////////////////////////////////////////////////////////////
  // EVE advantages
  // all the code is archiecture independant and can cope
  // with intel, arm, powerpc and will with risc5
  // simpler code and not need of splitting to insert or extract lanes.
