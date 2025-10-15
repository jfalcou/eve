#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <iomanip>

/**
 * This example demonstrates SIMD operations with different data types.
 *
 * We'll explore:
 * 1. Working with different numeric types (float, double, int, short)
 * 2. Converting between different SIMD types
 * 3. Handling different vector widths
 * 4. Performing operations specific to certain data types
 */

int main() {
  {
    using detail::print_m256;
    using detail::print_m256d;
    using detail::print_m256i;
    std::cout << "=== INTEL SIMD Operations with Different Data Types ===" << std::endl;
    std::cout << std::endl;

    // -------- 1. Float operations (32-bit) --------
    std::cout << "1. Float Operations (32-bit, 8 elements per vector)" << std::endl;

    // Initialize float vector
    __m256 float_vec1 = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    __m256 float_vec2 = _mm256_set1_ps(2.0f);  // Set all elements to 2.0

    // Perform operations
    __m256 float_sum = _mm256_add_ps(float_vec1, float_vec2);
    __m256 float_product = _mm256_mul_ps(float_vec1, float_vec2);

    // Print results
    print_m256(float_vec1, "Float Vector 1");
    print_m256(float_vec2, "Float Vector 2");
    print_m256(float_sum, "Sum (float_vec1 + float_vec2)");
    print_m256(float_product, "Product (float_vec1 * float_vec2)");
    std::cout << std::endl;

    // -------- 2. Double operations (64-bit) --------
    std::cout << "2. Double Operations (64-bit, 4 elements per vector)" << std::endl;

    // Initialize double vector
    __m256d double_vec1 = _mm256_set_pd(4.0, 3.0, 2.0, 1.0);
    __m256d double_vec2 = _mm256_set1_pd(3.0);  // Set all elements to 3.0

    // Perform operations
    __m256d double_sum = _mm256_add_pd(double_vec1, double_vec2);
    __m256d double_product = _mm256_mul_pd(double_vec1, double_vec2);

    // Print results
    print_m256d(double_vec1, "Double Vector 1");
    print_m256d(double_vec2, "Double Vector 2");
    print_m256d(double_sum, "Sum (double_vec1 + double_vec2)");
    print_m256d(double_product, "Product (double_vec1 * double_vec2)");
    std::cout << std::endl;

    // -------- 3. Integer operations (32-bit) --------
    std::cout << "3. Integer Operations (32-bit, 8 elements per vector)" << std::endl;

    // Initialize integer vector
    __m256i int_vec1 = _mm256_set_epi32(8, 7, 6, 5, 4, 3, 2, 1);
    __m256i int_vec2 = _mm256_set1_epi32(10);  // Set all elements to 10

    // Perform operations
    __m256i int_sum = _mm256_add_epi32(int_vec1, int_vec2);
    __m256i int_sub = _mm256_sub_epi32(int_vec1, int_vec2);

    // Print results
    print_m256i(int_vec1, "Int Vector 1");
    print_m256i(int_vec2, "Int Vector 2");
    print_m256i(int_sum, "Sum (int_vec1 + int_vec2)");
    print_m256i(int_sub, "Difference (int_vec1 - int_vec2)");
    std::cout << std::endl;

    // -------- 4. Type Conversions --------
    std::cout << "4. Type Conversions" << std::endl;

    // Convert float to integer (truncation)
    __m256i float_to_int = _mm256_cvttps_epi32(float_vec1);
    print_m256i(float_to_int, "Float to Int (truncated)");

    // Convert integer to float
    __m256 int_to_float = _mm256_cvtepi32_ps(int_vec1);
    print_m256(int_to_float, "Int to Float");

    // Convert between float and double (need to split/combine)
    // Extract lower 4 floats and convert to double
    __m128 float_low = _mm256_extractf128_ps(float_vec1, 0);
    __m256d float_to_double_low = _mm256_cvtps_pd(float_low);
    print_m256d(float_to_double_low, "Lower 4 Floats to Double");

    // Extract upper 4 floats and convert to double
    __m128 float_high = _mm256_extractf128_ps(float_vec1, 1);
    __m256d float_to_double_high = _mm256_cvtps_pd(float_high);
    print_m256d(float_to_double_high, "Upper 4 Floats to Double");
    std::cout << std::endl;

    // -------- 5. Bitwise Operations --------
    std::cout << "5. Bitwise Operations" << std::endl;

    // Create test vectors
    __m256i bits1 = _mm256_set1_epi32(0x0F0F0F0F);  // 00001111 00001111 00001111 00001111
    __m256i bits2 = _mm256_set1_epi32(0x33333333);  // 00110011 00110011 00110011 00110011

    // Perform bitwise operations
    __m256i bit_and = _mm256_and_si256(bits1, bits2);
    __m256i bit_or = _mm256_or_si256(bits1, bits2);
    __m256i bit_xor = _mm256_xor_si256(bits1, bits2);

    // Print results in hex format
    std::cout << "Bits1 (hex): 0x" << std::hex << std::setfill('0') << std::setw(8)
              << reinterpret_cast<int*>(&bits1)[0] << std::endl;
    std::cout << "Bits2 (hex): 0x" << std::hex << std::setfill('0') << std::setw(8)
              << reinterpret_cast<int*>(&bits2)[0] << std::endl;
    std::cout << "AND (hex): 0x" << std::hex << std::setfill('0') << std::setw(8)
              << reinterpret_cast<int*>(&bit_and)[0] << std::endl;
    std::cout << "OR (hex): 0x" << std::hex << std::setfill('0') << std::setw(8)
              << reinterpret_cast<int*>(&bit_or)[0] << std::endl;
    std::cout << "XOR (hex): 0x" << std::hex << std::setfill('0') << std::setw(8)
              << reinterpret_cast<int*>(&bit_xor)[0] << std::endl;
    std::cout << std::dec << std::endl;  // Reset to decimal

    // -------- 6. Specialized Operations --------
    std::cout << "6. Specialized Operations" << std::endl;

    // Horizontal addition (add adjacent pairs)
    __m256 hadd_result = _mm256_hadd_ps(float_vec1, float_vec2);
    print_m256(hadd_result, "Horizontal Add (pairs from float_vec1, float_vec2)");

    // Permute (rearrange elements)
    __m256 permute_result = _mm256_permute_ps(float_vec1, 0b10010011);
    print_m256(permute_result, "Permuted float_vec1");

    // Blend (select elements from two vectors based on mask)
    __m256 blend_result = _mm256_blend_ps(float_vec1, float_vec2, 0b10101010);
    print_m256(blend_result, "Blend of float_vec1 and float_vec2");
  }
  {
    std::cout << "=== EVE SIMD Operations with Different Data Types ===" << std::endl;
    std::cout << std::endl;

    auto print = [](auto val, std::string s){ //for all types
      std::cout << s << " = " << val << std::endl;
    };

    auto ops = [print](std::string typ, auto vec1, auto vec2){

      // Perform operations
      auto sum = vec1 + vec2;
      auto product = vec1 * vec2;

      // Print results
      std::cout << "type of element: " << typ << std::endl;
      print(vec1, "Float Vector 1");
      print(vec2, "Float Vector 2");
      print(sum, "Sum (vec1 + vec2)");
      print(product, "Product (vec1 * vec2)");
      std::cout << std::endl;
    };

    // -------- 1. Float operations (32-bit) --------
    std::cout << "1. Float Operations (32-bit, 8 elements per vector)" << std::endl;
    // Initialize float vector
    eve::wide float_vec1(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    eve::wide<float, eve::fixed<8>> float_vec2(2.0f);  // Set all elements to 2.0
    ops("float", float_vec1, float_vec2);

    // -------- 2. Double operations (64-bit) --------
    std::cout << "2. Double Operations (64-bit, 4 elements per vector)" << std::endl;

    // Initialize double vector
    eve::wide double_vec1(4.0, 3.0, 2.0, 1.0);
    eve::wide<double, eve::fixed<4>> double_vec2(3.0);  // Set all elements to 3.0
    ops("double", double_vec1, double_vec2);

    std::cout << "2b. Double Operations (64-bit, 8 elements per vector)" << std::endl;

    // Initialize double vector
    eve::wide double_vec3(8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);
    eve::wide<double, eve::fixed<8>> double_vec4(3.0);  // Set all elements to 3.0
    ops("double", double_vec3, double_vec4);

    // -------- 3. int operations (32-bit) --------
    std::cout << "2. int Operations (32-bit, 8 elements per vector)" << std::endl;

    // Initialize int vector
    eve::wide int_vec1(8, 7, 6, 5, 4, 3, 2, 1);
    eve::wide<int, eve::fixed<8>> int_vec2(10);  // Set all elements to 10
    ops("int", int_vec1, int_vec2);

    // -------- 3b. int operations (64-bit) --------
    std::cout << "2b. int Operations (64-bit, 8 elements per vector)" << std::endl;

    using wu64_t = eve::wide<std::uint64_t, eve::fixed<8>>;
    // Initialize longint vector
    wu64_t longint_vec1(8ull, 7ull, 6ull, 5ull, 4ull, 3ull, 2ull, 1ull);
    wu64_t longint_vec2(100ull);  // Set all elements to 100
    ops("longint", longint_vec1, longint_vec2);

    // -------- 4. Type Conversions --------
    std::cout << "4. Type Conversions" << std::endl;

    // Convert float to integer (truncation)
    auto float_to_int = eve::convert(float_vec1, eve::as<int>());
    print(float_to_int, "float to int");

   // Convert integer to float
    auto int_to_float = eve::convert(int_vec1, eve::as<float>());
    print(int_to_float, "Int to Float");

    // Convert between float and double (does not need to split/combine)
    auto float_to_double =  eve::convert(float_vec1, eve::as<double>());
    print(float_to_double, "Float to Double");

    // -------- 5. Bitwise Operations --------
    std::cout << "5. Bitwise Operations" << std::endl;

    using wi8_t = eve::wide<int, eve::fixed<8>>;
     // Create test vectors
    wi8_t bits1(0x0F0F0F0F);  // 00001111 00001111 00001111 00001111
    wi8_t bits2(0x33333333);  // 00110011 00110011 00110011 00110011

    // Perform bitwise operations
    auto  bit_and = bits1 & bits2;
    auto  bit_or  = bits1 | bits2;
    auto  bit_xor = bits1 ^ bits2;
    std::cout << std::hex;
    print(  bits1  , "bits1   (hex)");
    print(  bits2  , "bits2   (hex)");
    print(  bit_and, "bit_and (hex)");
    print(  bit_or , "bit_or  (hex)");
    print(  bit_xor, "bit_xor (hex)");
    std::cout << std::dec; // Reset to decimal

    // -------- 6. Specialized Operations --------

    std::cout << "6. Specialized Operations" << std::endl;

    // Horizontal addition (add adjacent pairs)
    TO DO
    //    __m256 hadd_result = _mm256_hadd_ps(float_vec1, float_vec2);
    //     print_m256(hadd_result, "Horizontal Add (pairs from float_vec1, float_vec2)");

    // Permute (rearrange elements) giving the final positions of the initial values
    auto permute_result = eve::shuffle(float_vec1, eve::pattern<4, 7, 6, 5, 0, 3, 2, 1>);
    print(float_vec1, "float_vec1");
    print(permute_result, "Permuted float_vec1");

    // Blend (select elements from two vectors based on mask)
    auto blend_result = eve::blend(float_vec1, float_vec2, eve::pattern<1, 0, 1, 0, 1, 0, 1, 0>);
    print(blend_result, "blend_result");
    // other way to do it
    auto blend_resultb = eve::blend(float_vec1, float_vec2, [](auto i, auto /*size*/){return i%2 == 0; });
    print(blend_resultb, "blend_result");

    return 0;
  }
}
