#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>


/**
 * 01_Basics/03_binding_with_unions - Techniques for accessing SIMD data
 *
 * This example demonstrates different ways to access and manipulate data in SIMD vectors:
 * 1. Using pointer conversion (reinterpret_cast)
 * 2. Using unions to create an alias between SIMD types and arrays
 * 3. Using the _mm256_store_* and _mm256_load_* functions
 * 4. Using the extract and insert element functions
 *
 * Each method has its advantages and use cases.
 */

int main() {
  {
    std::cout << "=== Accessing SIMD Data ===" << std::endl;
    std::cout << std::endl;

    // --------- 1. Pointer Conversion -------------
    std::cout << "1. Pointer Conversion" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using reinterpret_cast to convert between SIMD types and arrays." << std::endl;
    std::cout << "This is a simple but potentially unsafe method." << std::endl;
    std::cout << std::endl;

    // Initialize a SIMD vector with ascending values
    __m256 simd_vec1 = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    // Access the data using pointer conversion
    float* float_ptr = reinterpret_cast<float*>(&simd_vec1);

    // Print the data
    std::cout << "SIMD vector values via pointer: [";
    for (int i = 0; i < 7; i++) {
        std::cout << float_ptr[i] << ", ";
    }
    std::cout << float_ptr[7] << "]" << std::endl;

    // Modify the data through the pointer
    std::cout << "Modifying values via pointer..." << std::endl;
    float_ptr[0] = 100.0f;
    float_ptr[4] = 200.0f;

    // Print the modified SIMD vector
      detail::print_m256(simd_vec1, "Modified SIMD vector");
    std::cout << std::endl;

    // --------- 2. Using Unions -------------
    std::cout << "2. Using Unions" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using unions to create an alias between SIMD types and arrays." << std::endl;
    std::cout << "This is a cleaner and safer approach than pointer conversion." << std::endl;
    std::cout << std::endl;

    // Define a union for float SIMD vector
    union FloatSIMD {
        __m256 v;
        float a[8];
    };

    // Initialize the union with a SIMD vector
    FloatSIMD float_union;
    float_union.v = _mm256_set_ps(16.0f, 14.0f, 12.0f, 10.0f, 8.0f, 6.0f, 4.0f, 2.0f);

    // Access the data through the array
    std::cout << "SIMD vector values via union: [";
    for (int i = 0; i < 7; i++) {
        std::cout << float_union.a[i] << ", ";
    }
    std::cout << float_union.a[7] << "]" << std::endl;

    // Modify the data through the array
    std::cout << "Modifying values via union..." << std::endl;
    float_union.a[1] = 42.0f;
    float_union.a[6] = 99.0f;

    // Print the modified SIMD vector
    detail::print_m256(float_union.v, "Modified SIMD vector (union)");

    // Using our utility union from simd_utils.h
    detail::float8 float8_union;
    float8_union.v = _mm256_set1_ps(5.0f);
    float8_union.a[2] = 10.0f;
    float8_union.a[5] = 20.0f;

    detail::print_m256(float8_union.v, "Using float8 union from simd_utils.h");
    std::cout << std::endl;

    // --------- 3. Store and Load Functions -------------
    std::cout << "3. Store and Load Functions" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using _mm256_store_* and _mm256_load_* functions to transfer data." << std::endl;
    std::cout << "This is the recommended approach for most situations." << std::endl;
    std::cout << std::endl;

    // Initialize a SIMD vector
    __m256 simd_vec3 = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    // Allocate aligned memory for the array
    float* aligned_array = detail::aligned_alloc<float>(8);

    // Store the SIMD vector to the array
    _mm256_store_ps(aligned_array, simd_vec3);

    // Print the array
    std::cout << "SIMD vector values via store: [";
    for (int i = 0; i < 7; i++) {
        std::cout << aligned_array[i] << ", ";
    }
    std::cout << aligned_array[7] << "]" << std::endl;

    // Modify the array
    std::cout << "Modifying values in the array..." << std::endl;
    aligned_array[3] = 30.0f;
    aligned_array[7] = 80.0f;

    // Load the modified array back to a SIMD vector
    __m256 modified_vec = _mm256_load_ps(aligned_array);

    // Print the modified SIMD vector
    detail::print_m256(modified_vec, "Modified SIMD vector (store/load)");
    std::cout << std::endl;

    // --------- 4. Extract and Insert Elements -------------
    std::cout << "4. Extract and Insert Elements" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using _mm256_extract_* and _mm256_insert_* functions to access individual elements." << std::endl;
    std::cout << "This is useful when you only need to access a few elements." << std::endl;
    std::cout << std::endl;

    // Initialize a SIMD vector with integers
    __m256i simd_int_vec = _mm256_set_epi32(8, 7, 6, 5, 4, 3, 2, 1);

    // Extract individual elements
    // Note: For AVX2, we need to extract 128-bit lanes first, then extract from those
    __m128i low_lane = _mm256_extracti128_si256(simd_int_vec, 0);  // Extract lower 128 bits
    __m128i high_lane = _mm256_extracti128_si256(simd_int_vec, 1); // Extract upper 128 bits

    int element0 = _mm_extract_epi32(low_lane, 0);  // Extract element 0
    int element3 = _mm_extract_epi32(low_lane, 3);  // Extract element 3
    int element4 = _mm_extract_epi32(high_lane, 0); // Extract element 4
    int element7 = _mm_extract_epi32(high_lane, 3); // Extract element 7

    std::cout << "Extracted elements: " << element0 << ", " << element3 << ", "
              << element4 << ", " << element7 << std::endl;

    // Insert elements
    // For inserting, we need to create new 128-bit vectors and then combine them
    __m128i new_low = _mm_insert_epi32(low_lane, 100, 1);  // Replace element 1
    __m128i new_high = _mm_insert_epi32(high_lane, 200, 2); // Replace element 6

    // Combine the lanes back into a 256-bit vector
    __m256i modified_int_vec = _mm256_setr_m128i(new_low, new_high);

    // Print the modified vector
    detail::print_m256i(modified_int_vec, "Modified integer vector (extract/insert)");

    // Clean up
    free(aligned_array);
  }
  {

    auto print = [](auto val, std::string s){ //for all simd types
      std::cout << s << " = " << val << std::endl;
    };

    auto printa = [] (auto a, std::string s){    // Print  array
      constexpr int N = a.size();
      std::cout << s << " = ";
      for (int i = 0; i < N-1; ++i)   std::cout << a[i] << ", ";
      std::cout << a[N-1] << std::endl;
    };

    std::cout << "===  EVE Accessing SIMD Data ===" << std::endl;
    std::cout << std::endl;

    // --------- 1. Pointer Conversion -------------
    std::cout << "1. Pointer Conversion" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using reinterpret_cast to convert between SIMD types and arrays." << std::endl;
    std::cout << "This is a simple but potentially unsafe method." << std::endl;
    std::cout << "AND IT IS DISCOURAGED : prefer using get and set method to access individual lanes, " << std::endl;
    std::cout << "which is not desired in most simd programs" << std::endl;
    std::cout << std::endl;

    // Initialize a SIMD vector with ascending values
    eve::wide vec1(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    // Print the data
    print(vec1, "vec1");

    // Modify the data through the set function
    std::cout << "Modifying values via pointer..." << std::endl;
    vec1.set(0, 100.0f);
    vec1.set(4, 200.0f);

    // Print the mofified data
    print(vec1, "vec1");

    // --------- 2. Using Unions -------------
    std::cout << "2. Using Unions" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using unions to create an alias between SIMD types and arrays." << std::endl;
    std::cout << "EVE does not consider this appeoch cleaner nor safer approach than pointer conversion." << std::endl;
    std::cout << "as access to non initialized member is a priori U.B. in C++"<< std::endl;
    std::cout << "To transform an simd vector to an array of scalars you can use bit_cast, "<< std::endl;
    std::cout << "but this create an independant array."<< std::endl;
    std::cout << std::endl;

    // Initialize a SIMD vector with ascending values
    eve::wide vec2(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    using a8_t =   std::array<float, 8>;
    alignas(sizeof(eve::wide<float>)) a8_t avec2 = eve::bit_cast(vec2, eve::as<a8_t>());

    for(int i=0; i < 8 ; ++i) std::cout << avec2[i] << " ";
    std::cout << std::endl;

    // --------- 3. Store and Load Functions -------------
    std::cout << "3. Store and Load Functions" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using _eve::store_* and eve::load_* functions to transfer data." << std::endl;
    std::cout << "This is the recommended approach for most situations." << std::endl;
    std::cout << std::endl;

   // Initialize a SIMD vector
    eve::wide vec3 (8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

    // Allocate aligned memory for the array
    alignas(sizeof(eve::wide<float>)) a8_t aligned_array;

    // Store the SIMD vector to the array
    eve::store(vec3, &aligned_array[0]);

    // Print the array
    printa(aligned_array, "aligned_array via store");
    std::cout << "SIMD vector values via store: [";


    // Modify the array
    std::cout << "Modifying values in the array..." << std::endl;
    aligned_array[3] = 30.0f;
    aligned_array[7] = 80.0f;

    // Load the modified array back to a SIMD vector
    auto modified_vec = eve::load(&aligned_array[0], eve::fixed<aligned_array.size()>());

    // Print the modified SIMD vector
    print(modified_vec, "Modified SIMD vector (store/load)");
    std::cout << std::endl;

    // --------- 4. Extract and Insert Elements -------------
    std::cout << "4. Extract and Insert Elements" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Using eve::get and eve::set_* functions to access individual elements." << std::endl;
    std::cout << "This is useful when you only need to access a few elements." << std::endl;
    std::cout << std::endl;

    // Initialize a SIMD vector with integers
    eve::wide int_vec(8, 7, 6, 5, 4, 3, 2, 1);

    // Extract individual elements
    // Note: EVE manages the splitting if necessary

    int element0 = int_vec.get(0);  // Extract element 0
    int element3 = int_vec.get(3);  // Extract element 3
    int element4 = int_vec.get(4);  // Extract element 4
    int element7 = int_vec.get(7);  // Extract element 7

    std::cout << "Extracted elements: " << element0 << ", " << element3 << ", "
              << element4 << ", " << element7 << std::endl;

    // Insert elements
    // EVE does not need to create new 128-bit vectors and then combine them
    auto modified_int_vec = int_vec;
    modified_int_vec.set(1, 100);// Replace element 1
    modified_int_vec.set(6, 200); // Replace element 6

    // Print the modified vector
    print(modified_int_vec, "modified_int_vec");

}
  return 0;
}

  ////////////////////////////////////////////////////////////
  // EVE advantages
  // all the code is archiecture independant and can cope
  // with intel, arm, powerpc and will with risc5
  // simpler code and not need of splitting to insert or extract lanes.
