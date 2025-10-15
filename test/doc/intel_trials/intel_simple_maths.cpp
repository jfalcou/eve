#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>

/**
 * 02_Computations/01_simple_maths - Basic SIMD mathematical operations
 *
 * This example demonstrates various mathematical operations using EVE:
 * 1. Addition (add or +)
 * 2. Subtraction (sub or -)
 * 3. Multiplication (mul or *)
 * 4. Division (div or /)
 * 5. Fused Multiply-Add (fma)
 * 6. Square Root (sqrt)
 * 7. Minimum/Maximum (min max)
 * 8. Horizontal operations (_mm256_hadd_ps, _mm256_hsub_ps)
 *
 * For each operation, we compare the performance of SIMD vs. scalar implementation.
 */

int main() {
  {
    std::cout << "=== Intel SIMD Mathematical Operations ===" << std::endl;
    std::cout << std::endl;

    // Initialize test data
    float data1[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    float data2[8] = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};

    // Load data into SIMD vectors
    __m256 vector1 = _mm256_loadu_ps(data1);
    __m256 vector2 = _mm256_loadu_ps(data2);

    // --------- 1. Addition -------------
    std::cout << "1. Addition (_mm256_add_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Adds corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Print input vectors
    detail::print_m256(vector1, "Vector 1");
    detail::print_m256(vector2, "Vector 2");

    // Perform addition
    __m256 add_result = _mm256_add_ps(vector1, vector2);
    detail::print_m256(add_result, "Addition Result (Vector 1 + Vector 2)");

    // Compare performance: scalar vs. SIMD
 //    auto scalar_add = [&]() {
//         float result[8];
//         for (int i = 0; i < 8; i++) {
//             result[i] = data1[i] + data2[i];
//         }
//     };

//     auto simd_add = [&]() {
//         __m256 result = _mm256_add_ps(vector1, vector2);
//     };

//     benchmark_comparison("Addition", scalar_add, simd_add);
//     std::cout << std::endl;

    // --------- 2. Subtraction -------------
    std::cout << "2. Subtraction (_mm256_sub_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Subtracts corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Perform subtraction
    __m256 sub_result = _mm256_sub_ps(vector1, vector2);
    detail::print_m256(sub_result, "Subtraction Result (Vector 1 - Vector 2)");

//     // Compare performance: scalar vs. SIMD
//     auto scalar_sub = [&]() {
//         float result[8];
//         for (int i = 0; i < 8; i++) {
//             result[i] = data1[i] - data2[i];
//         }
//     };

//     auto simd_sub = [&]() {
//         __m256 result = _mm256_sub_ps(vector1, vector2);
//     };

//     benchmark_comparison("Subtraction", scalar_sub, simd_sub);
//     std::cout << std::endl;

    // --------- 3. Multiplication -------------
    std::cout << "3. Multiplication (_mm256_mul_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Multiplies corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Perform multiplication
    __m256 mul_result = _mm256_mul_ps(vector1, vector2);
    detail::print_m256(mul_result, "Multiplication Result (Vector 1 * Vector 2)");

    // Compare performance: scalar vs. SIMD
//     auto scalar_mul = [&]() {
//         float result[8];
//         for (int i = 0; i < 8; i++) {
//             result[i] = data1[i] * data2[i];
//         }
//     };

//     auto simd_mul = [&]() {
//         __m256 result = _mm256_mul_ps(vector1, vector2);
//     };

//     benchmark_comparison("Multiplication", scalar_mul, simd_mul);
//     std::cout << std::endl;

    // --------- 4. Division -------------
    std::cout << "4. Division (_mm256_div_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Divides corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Perform division
    __m256 div_result = _mm256_div_ps(vector1, vector2);
    detail::print_m256(div_result, "Division Result (Vector 1 / Vector 2)");

    // Compare performance: scalar vs. SIMD
//     auto scalar_div = [&]() {
//         float result[8];
//         for (int i = 0; i < 8; i++) {
//             result[i] = data1[i] / data2[i];
//         }
//     };

//     auto simd_div = [&]() {
//         __m256 result = _mm256_div_ps(vector1, vector2);
//     };

//     benchmark_comparison("Division", scalar_div, simd_div);
//     std::cout << std::endl;

    // --------- 5. Fused Multiply-Add -------------
    std::cout << "5. Fused Multiply-Add (_mm256_fmadd_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Performs a fused multiply-add operation: a*b + c" << std::endl;
    std::cout << "This is more accurate and faster than separate multiply and add." << std::endl;
    std::cout << std::endl;

    // Create a third vector for FMA
    __m256 vector3 = _mm256_set1_ps(2.0f);
    detail::print_m256(vector3, "Vector 3");

    // Perform FMA: vector1 * vector2 + vector3
    __m256 fma_result = _mm256_fmadd_ps(vector1, vector2, vector3);
    detail::print_m256(fma_result, "FMA Result (Vector 1 * Vector 2 + Vector 3)");

    // Compare performance: scalar vs. SIMD
//     auto scalar_fma = [&]() {
//         float result[8];
//         for (int i = 0; i < 8; i++) {
//             result[i] = data1[i] * data2[i] + 2.0f;
//         }
//     };

//     auto simd_fma = [&]() {
//         __m256 result = _mm256_fmadd_ps(vector1, vector2, vector3);
//     };

//     benchmark_comparison("Fused Multiply-Add", scalar_fma, simd_fma);
//     std::cout << std::endl;

    // --------- 6. Square Root -------------
    std::cout << "6. Square Root (_mm256_sqrt_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Computes the square root of each element in a vector." << std::endl;
    std::cout << std::endl;

    // Create a vector of positive values
    __m256 pos_vector = _mm256_set_ps(64.0f, 49.0f, 36.0f, 25.0f, 16.0f, 9.0f, 4.0f, 1.0f);
    detail::print_m256(pos_vector, "Input Vector");

    // Compute square root
    __m256 sqrt_result = _mm256_sqrt_ps(pos_vector);
    detail::print_m256(sqrt_result, "Square Root Result");

//     // Compare performance: scalar vs. SIMD
//     auto scalar_sqrt = [&]() {
//         float result[8];
//         union {
//             __m256 v;
//             float a[8];
//         } u;
//         u.v = pos_vector;
//         for (int i = 0; i < 8; i++) {
//             result[i] = std::sqrt(u.a[i]);
//         }
//     };

//     auto simd_sqrt = [&]() {
//         __m256 result = _mm256_sqrt_ps(pos_vector);
//     };

//     benchmark_comparison("Square Root", scalar_sqrt, simd_sqrt);
//     std::cout << std::endl;

    // --------- 7. Min/Max Operations -------------
    std::cout << "7. Min/Max Operations (_mm256_min_ps, _mm256_max_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Computes the minimum or maximum of corresponding elements." << std::endl;
    std::cout << std::endl;

    // Print input vectors again
    detail::print_m256(vector1, "Vector 1");
    detail::print_m256(vector2, "Vector 2");

    // Compute min and max
    __m256 min_result = _mm256_min_ps(vector1, vector2);
    __m256 max_result = _mm256_max_ps(vector1, vector2);

    detail::print_m256(min_result, "Minimum Result");
    detail::print_m256(max_result, "Maximum Result");

//     // Compare performance: scalar vs. SIMD for min
//     auto scalar_min = [&]() {
//         float result[8];
//         for (int i = 0; i < 8; i++) {
//             result[i] = std::min(data1[i], data2[i]);
//         }
//     };

//     auto simd_min = [&]() {
//         __m256 result = _mm256_min_ps(vector1, vector2);
//     };

//     benchmark_comparison("Minimum", scalar_min, simd_min);
//    std::cout << std::endl;

    // --------- 8. Horizontal Operations -------------
    std::cout << "8. Horizontal Operations (_mm256_hadd_ps, _mm256_hsub_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Performs horizontal addition or subtraction of adjacent elements." << std::endl;
    std::cout << std::endl;

    // Create test vectors
    __m256 hadd_vec1 = _mm256_set_ps(8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    __m256 hadd_vec2 = _mm256_set_ps(16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f);

    detail::print_m256(hadd_vec1, "Vector A");
    detail::print_m256(hadd_vec2, "Vector B");

    // Perform horizontal addition
    // This adds adjacent pairs: (a0+a1, a2+a3, b0+b1, b2+b3, a4+a5, a6+a7, b4+b5, b6+b7)
    __m256 hadd_result = _mm256_hadd_ps(hadd_vec1, hadd_vec2);
    detail::print_m256(hadd_result, "Horizontal Addition Result");

    // Perform horizontal subtraction
    // This subtracts adjacent pairs: (a0-a1, a2-a3, b0-b1, b2-b3, a4-a5, a6-a7, b4-b5, b6-b7)
    __m256 hsub_result = _mm256_hsub_ps(hadd_vec1, hadd_vec2);
    detail::print_m256(hsub_result, "Horizontal Subtraction Result");

    // Note: Horizontal operations are typically slower than vertical operations
    // They are useful for specific algorithms like dot products and matrix operations

  }
  {
    std::cout << "=== SIMD Mathematical Operations ===" << std::endl;
    std::cout << std::endl;

    // Initialize test data
    float data1[8] = {1.2f, 2.0f, 3.0f, 4.3f, 5.0f, 6.0f, 7.0f, 8.0f};
    float data2[8] = {8.0f, 7.0f, 6.4f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    using w_t = eve::wide<float, eve::fixed<8>>;
    // Load data into SIMD vectors
    w_t vector1 = eve::load(data1);
    w_t vector2 = eve::load(data2);

    // --------- 1. Addition -------------
    std::cout << "1. Addition (eve::add or +" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Adds corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Print input vectors
    std::cout <<  "Vector1 " << vector1 << std::endl;
    std::cout <<  "Vector2 " << vector2 << std::endl;

    // Perform addition
    auto add_result = eve::add(vector1, vector2);
    std::cout << "Addition Result (Vector 1 + Vector 2)" << add_result << std::endl; ;


    // --------- 2. Subtraction -------------
    std::cout << "2. Subtraction (eve::sub or -)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Subtracts corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Perform subtraction
    auto sub_result = eve::sub(vector1, vector2);
    std::cout << "Subtraction Result (Vector 1 - Vector 2)" << sub_result << std::endl; ;
    std::cout << std::endl;

    // --------- 3. Multiplication -------------
    std::cout << "3. Multiplication (eve::mul or *)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Multiplies corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

    // Perform Multiplication
    auto mul_result = eve::mul(vector1, vector2);
    std::cout << "Multiplication Result (Vector 1 * Vector 2)" << mul_result << std::endl; ;
    std::cout << std::endl;


    // --------- 4. Division -------------
    std::cout << "4. Division eve::divor /" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Divides corresponding elements of two vectors." << std::endl;
    std::cout << std::endl;

     // Perform division
    auto div_result = eve::mul(vector1, vector2);
    std::cout << "Multiplication Result (Vector 1 / Vector 2)" << div_result << std::endl;
    std::cout << std::endl;

    // --------- 5. Fused Multiply-Add -------------
    std::cout << "5. Fused Multiply-Add (fma)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Performs a fused multiply-add operation: a*b + c" << std::endl;
    std::cout << "This is more accurate and faster than separate multiply and add." << std::endl;
    std::cout << "Even If not present in harware (-msse2 for instance) " << std::endl;
    std::cout << "the correct fma behaviouris emulated using the pedantic option." << std::endl;
    std::cout << std::endl;

    // Create a third vector for FMA
    w_t vector3(2.0f);
    std::cout << "vector3 " << vector3 << std::endl;


    // Perform FMA: vector1 * vector2 + vector3
    auto fma_result = eve::fma[eve::pedantic](vector1, vector2, vector3);
    std::cout << "FMA Result (Vector 1 * Vector 2 + Vector 3) " << fma_result << std::endl;
    std::cout << std::endl;

    // --------- 6. Square Root -------------
    std::cout << "6. Square Root (_mm256_sqrt_ps)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Computes the square root of each element in a vector." << std::endl;
    std::cout << std::endl;

    // Create a vector of positive values
    w_t pos_vector{64.0f, 49.0f, 36.0f, 25.0f, 16.0f, 9.0f, 4.0f, 1.0f};
    std::cout << "Input Vector " << pos_vector << std::endl;;

    // Compute square root
    auto sqrt_result =eve::sqrt(pos_vector);
    std::cout << "Square Root Result " << sqrt_result << std::endl;
    std::cout << std::endl;

    // --------- 7. Min/Max Operations -------------
    std::cout << "7. Min/Max Operations (min, max)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Computes the minimum or maximum of corresponding elements." << std::endl;
    std::cout << std::endl;

    // Print input vectors again
    // Print input vectors
    std::cout <<  "Vector1 " << vector1 << std::endl;
    std::cout <<  "Vector2 " << vector2 << std::endl;

    // Compute min and max
    auto min_result = eve::min(vector1, vector2);
    auto max_result = eve::max(vector1, vector2);

    std::cout <<  "Minimum Result " << min_result << std::endl;
    std::cout <<  "Maximum Result " << max_result << std::endl;

    return 0;
}
  ////////////////////////////////////////////////////////////
  // Intel disadvantages
  // needs intel architecture and  does not work if avx2 and fma are not available
  ////////////////////////////////////////////////////////////
  // EVE advantages
  // all the code is archiecture independant and can cope
  // with intel arm and powerpc and will with risc5
  // simpler code and very large available (simd andscalar compatible) functions panel.
  // infix notation can be used.
  // operators are overloaded on all scalar and simd available data types
  // the named operators can be used with numerous option as saturatde,  widen etc.
  // the named operators can be used with mutiple parameters (not only 2)
  // and are vectorized automagically if all the parameters are numerous enough scalars
  // to expect a speed up
  // if no hardware fma is available the code just do a*b+c but the option pedantic
  // used with fma can guarantee correct fma behaviour (of course at the emulation price ~17 cycles
  // per call.
}
