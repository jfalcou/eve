#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

/**
 * 02_Computations/02_dot_product - Implementing vector dot products with SIMD
 *
 * This example demonstrates different ways to calculate dot products using SIMD:
 * 1. Scalar implementation (baseline)
 * 2. Basic SIMD implementation using separate vectors for x, y, z components
 * 3. SIMD implementation with Structure of Arrays (SoA) layout
 * 4. SIMD implementation with horizontal addition
 * 5. SIMD implementation for large arrays (batch processing)
 *
 * The dot product is a fundamental operation in many fields including:
 * - Computer graphics (lighting calculations, projections)
 * - Machine learning (neural networks, similarity measures)
 * - Physics simulations (force calculations)
 */

// 3D vector structure (Array of Structures layout)
struct Vec3 {
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    // Scalar dot product
    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

// Structure of Arrays layout for better SIMD performance
struct Vec3Array {
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;

    Vec3Array(size_t size) : x(size), y(size), z(size) {}

    void set(size_t index, float x_val, float y_val, float z_val) {
        x[index] = x_val;
        y[index] = y_val;
        z[index] = z_val;
    }

    void set(size_t index, const Vec3& vec) {
        x[index] = vec.x;
        y[index] = vec.y;
        z[index] = vec.z;
    }
};

// Generate random 3D vectors
std::vector<Vec3> generateRandomVectors(size_t count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    std::vector<Vec3> vectors;
    vectors.reserve(count);

    for (size_t i = 0; i < count; i++) {
        vectors.emplace_back(dist(gen), dist(gen), dist(gen));
    }

    return vectors;
}

// Convert Array of Structures to Structure of Arrays
Vec3Array convertToSoA(const std::vector<Vec3>& vectors) {
    Vec3Array result(vectors.size());

    for (size_t i = 0; i < vectors.size(); i++) {
        result.set(i, vectors[i]);
    }

    return result;
}

// 1. Scalar dot product implementation
float scalarDotProduct(const std::vector<Vec3>& vectors1, const std::vector<Vec3>& vectors2) {
    float sum = 0.0f;
    for (size_t i = 0; i < vectors1.size(); i++) {
        sum += vectors1[i].dot(vectors2[i]);
    }
    return sum;
}

// 2. Basic SIMD dot product implementation (for 8 vectors at a time)
__m256 simdDotProduct8(const std::vector<Vec3>& vectors1, const std::vector<Vec3>& vectors2) {
    // Load x, y, z components into separate SIMD registers
    float x1[8], y1[8], z1[8];
    float x2[8], y2[8], z2[8];

    for (int i = 0; i < 8; i++) {
        x1[i] = vectors1[i].x;
        y1[i] = vectors1[i].y;
        z1[i] = vectors1[i].z;
        x2[i] = vectors2[i].x;
        y2[i] = vectors2[i].y;
        z2[i] = vectors2[i].z;
    }

    // Load data into SIMD registers
    __m256 vx1 = _mm256_loadu_ps(x1);
    __m256 vy1 = _mm256_loadu_ps(y1);
    __m256 vz1 = _mm256_loadu_ps(z1);
    __m256 vx2 = _mm256_loadu_ps(x2);
    __m256 vy2 = _mm256_loadu_ps(y2);
    __m256 vz2 = _mm256_loadu_ps(z2);

    // Compute dot products using FMA (Fused Multiply-Add)
    // (x1*x2 + y1*y2 + z1*z2)
    __m256 result = _mm256_mul_ps(vx1, vx2);                  // x1*x2
    result = _mm256_fmadd_ps(vy1, vy2, result);               // x1*x2 + y1*y2
    result = _mm256_fmadd_ps(vz1, vz2, result);               // x1*x2 + y1*y2 + z1*z2

    return result;
}

// 3. SIMD dot product with Structure of Arrays layout
__m256 simdDotProductSoA8(const Vec3Array& vectors1, const Vec3Array& vectors2, size_t offset) {
    // Load data into SIMD registers directly from SoA structure
    __m256 vx1 = _mm256_loadu_ps(&vectors1.x[offset]);
    __m256 vy1 = _mm256_loadu_ps(&vectors1.y[offset]);
    __m256 vz1 = _mm256_loadu_ps(&vectors1.z[offset]);
    __m256 vx2 = _mm256_loadu_ps(&vectors2.x[offset]);
    __m256 vy2 = _mm256_loadu_ps(&vectors2.y[offset]);
    __m256 vz2 = _mm256_loadu_ps(&vectors2.z[offset]);

    // Compute dot products using FMA (Fused Multiply-Add)
    __m256 result = _mm256_mul_ps(vx1, vx2);
    result = _mm256_fmadd_ps(vy1, vy2, result);
    result = _mm256_fmadd_ps(vz1, vz2, result);

    return result;
}

// 4. SIMD dot product with horizontal addition (for a single dot product)
float simdDotProductSingle(const Vec3& v1, const Vec3& v2) {
    // Load vector components into SIMD registers
    __m128 vec1 = _mm_setr_ps(v1.x, v1.y, v1.z, 0.0f);
    __m128 vec2 = _mm_setr_ps(v2.x, v2.y, v2.z, 0.0f);

    // Multiply components
    __m128 mul = _mm_mul_ps(vec1, vec2);

    // Horizontal addition to sum up components
    // First add pairs: (x+y, z+0, x+y, z+0)
    __m128 hadd1 = _mm_hadd_ps(mul, mul);
    // Then add pairs again: (x+y+z+0, x+y+z+0, x+y+z+0, x+y+z+0)
    __m128 hadd2 = _mm_hadd_ps(hadd1, hadd1);

    // Extract the result (first element)
    return _mm_cvtss_f32(hadd2);
}

// 5. SIMD dot product for large arrays
float simdDotProductLarge(const Vec3Array& vectors1, const Vec3Array& vectors2) {
    size_t size = vectors1.x.size();
    size_t blocks = size / 8;
//    size_t remainder = size % 8;

    // Process 8 vectors at a time
    __m256 sum = _mm256_setzero_ps();
    for (size_t i = 0; i < blocks; i++) {
        __m256 dot8 = simdDotProductSoA8(vectors1, vectors2, i * 8);
        sum = _mm256_add_ps(sum, dot8);
    }

    // Horizontal sum of the 8 dot products
    float result_array[8];
    _mm256_storeu_ps(result_array, sum);
    float total = 0.0f;
    for (int i = 0; i < 8; i++) {
        total += result_array[i];
    }

    // Process remaining vectors
    for (size_t i = blocks * 8; i < size; i++) {
        Vec3 v1(vectors1.x[i], vectors1.y[i], vectors1.z[i]);
        Vec3 v2(vectors2.x[i], vectors2.y[i], vectors2.z[i]);
        total += v1.dot(v2);
    }

    return total;
}

int main() {

    // Generate random test vectors
    const size_t NUM_VECTORS = 1024;
    std::vector<Vec3> vectors1 = generateRandomVectors(NUM_VECTORS);
    std::vector<Vec3> vectors2 = generateRandomVectors(NUM_VECTORS);

    {
      std::cout << "=== Intel SIMD Dot Product Implementations ===" << std::endl;
      std::cout << std::endl;


      // Convert to Structure of Arrays for more efficient SIMD processing
      Vec3Array soa_vectors1 = convertToSoA(vectors1);
      Vec3Array soa_vectors2 = convertToSoA(vectors2);

      // --------- 1. Basic Dot Product Comparison -------------
      std::cout << "1. Basic Dot Product (8 vectors)" << std::endl;
      std::cout << "---------------------------------------------------" << std::endl;
      std::cout << "Comparing scalar vs. SIMD implementation for 8 vectors." << std::endl;
      std::cout << std::endl;

      // Calculate dot products using scalar method
      float scalar_results[8];
      for (int i = 0; i < 8; i++) {
        scalar_results[i] = vectors1[i].dot(vectors2[i]);
      }

      // Calculate dot products using SIMD
      __m256 simd_result = simdDotProduct8(vectors1, vectors2);
      float simd_results[8];
      _mm256_storeu_ps(simd_results, simd_result);

      // Print and compare results
      std::cout << "Scalar results: [";
      for (int i = 0; i < 7; i++) {
        std::cout << scalar_results[i] << ", ";
      }
      std::cout << scalar_results[7] << "]" << std::endl;

      std::cout << "SIMD results:   [";
      for (int i = 0; i < 7; i++) {
        std::cout << simd_results[i] << ", ";
      }
      std::cout << simd_results[7] << "]" << std::endl;
      std::cout << std::endl;

//     // --------- 2. Performance Comparison -------------
//     std::cout << "2. Performance Comparison" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Comparing performance of different dot product implementations." << std::endl;
//     std::cout << std::endl;

//     // Benchmark scalar implementation
//     auto scalar_benchmark = [&]() {
//         volatile float result = scalarDotProduct(vectors1, vectors2);
//     };

//     // Benchmark SIMD implementation with AoS layout
//     auto simd_aos_benchmark = [&]() {
//         float total = 0.0f;
//         for (size_t i = 0; i < NUM_VECTORS; i += 8) {
//             size_t remaining = std::min(size_t(8), NUM_VECTORS - i);
//             if (remaining < 8) break;  // Skip incomplete blocks for simplicity

//             std::vector<Vec3> block1(vectors1.begin() + i, vectors1.begin() + i + 8);
//             std::vector<Vec3> block2(vectors2.begin() + i, vectors2.begin() + i + 8);

//             __m256 result = simdDotProduct8(block1, block2);
//             float results[8];
//             _mm256_storeu_ps(results, result);

//             for (int j = 0; j < 8; j++) {
//                 total += results[j];
//             }
//         }
//     };

//     // Benchmark SIMD implementation with SoA layout
//     auto simd_soa_benchmark = [&]() {
//         volatile float result = simdDotProductLarge(soa_vectors1, soa_vectors2);
//     };

//     // Run benchmarks
//     benchmark_comparison("Dot Product (1024 vectors)", scalar_benchmark, simd_soa_benchmark);
//     std::cout << std::endl;

//     // --------- 3. Structure of Arrays vs Array of Structures -------------
//     std::cout << "3. Structure of Arrays vs Array of Structures" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Comparing AoS vs SoA memory layouts for SIMD processing." << std::endl;
//     std::cout << std::endl;

//     benchmark_comparison("AoS vs SoA", simd_aos_benchmark, simd_soa_benchmark);
//     std::cout << std::endl;

//     // --------- 4. Single Vector Dot Product -------------
//     std::cout << "4. Single Vector Dot Product" << std::endl;
//     std::cout << "---------------------------------------------------" << std::endl;
//     std::cout << "Using SIMD for a single dot product with horizontal addition." << std::endl;
//     std::cout << std::endl;

//     Vec3 v1(0.5f, -0.3f, 0.8f);
//     Vec3 v2(0.2f, 0.7f, -0.4f);

//     float scalar_dot = v1.dot(v2);
//     float simd_dot = simdDotProductSingle(v1, v2);

//     std::cout << "Vector 1: (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << std::endl;
//     std::cout << "Vector 2: (" << v2.x << ", " << v2.y << ", " << v2.z << ")" << std::endl;
//     std::cout << "Scalar dot product: " << scalar_dot << std::endl;
//     std::cout << "SIMD dot product:   " << simd_dot << std::endl;
//     std::cout << std::endl;

//     // Benchmark single vector dot product
//     auto scalar_single_benchmark = [&]() {
//         for (int i = 0; i < 1000; i++) {
//             volatile float result = v1.dot(v2);
//         }
//     };

//     auto simd_single_benchmark = [&]() {
//         for (int i = 0; i < 1000; i++) {
//             volatile float result = simdDotProductSingle(v1, v2);
//         }
//     };

//     benchmark_comparison("Single Dot Product (1000 iterations)", scalar_single_benchmark, simd_single_benchmark);
    }
    {
      std::cout << "=== EVE SIMD Dot Product Implementations ===" << std::endl;
      std::cout << std::endl;

      using vecf =  std::vector<float>;
      auto generateRandomVector = [](size_t count) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        std::vector<float> v;
        v.reserve(count);
        for (size_t i = 0; i < count; ++i) {
          v[i] = v.emplace_back(dist(gen));
        }
        return v;
      };

      auto print = [](std::string name, auto v){
        std::cout << name << " =  ";

        for(std::size_t i=0; i <  v.size(); ++i)
        {
          std::cout << v[i] << ((i != v.size()-1) ? ", ":"");
        }
        std::cout << std::endl;
      };

      auto dot = []( auto & d, auto const& x1, auto const& y1, auto const& z1
                   , auto const& x2, auto const& y2, auto const& z2)
      {
        d.resize(x1.size()); //d is sized appropriatly
        auto dot_it = [](auto e){
          auto [xx1, yy1, zz1, xx2, yy2, zz2] = e;
          return eve::dot(xx1, yy1, zz1, xx2, yy2, zz2);
        };
        // the algo transform_to takes care of using simd chunks
        // the dot function performs dot products on 2n scalars or 2n simd vectors elementwise (see the eve documentation)
        // the input vector size need not be a multiple of (the automagically chosen) best SIMD vector size
        // unroll option is not needed but can tune the performance
        eve::algo::transform_to[eve::algo::unroll<2>](eve::algo::views::zip(x1, y1, z1, x2, y2, z2), d, dot_it);
      };

      //generating three vectors for x y and z coordinates as usual scalar based datas
      auto cnt = 9;
      vecf x1(generateRandomVector(cnt));
      vecf y1(generateRandomVector(cnt));
      vecf z1(generateRandomVector(cnt));
      vecf x2(generateRandomVector(cnt));
      vecf y2(generateRandomVector(cnt));
      vecf z2(generateRandomVector(cnt));

      print("x1 ", x1);
      print("y1 ", y1);
      print("z1 ", z1);
      print("x2 ", x2);
      print("y2 ", y2);
      print("z2 ", z2);
      std::cout << std::endl;
      vecf d;
      print("dot product ", (dot(d, x1, y1, z1, x2, y2, z2), d));
    }

    return 0;
}
