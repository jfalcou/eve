#include "detail/intel_utils.hpp"
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

/**
 * This example demonstrates using SIMD for basic image processing operations.
 *
 * We'll implement:
 * 1. Brightness adjustment
 * 2. Contrast enhancement
 * 3. Image blurring (simple box filter)
 * 4. Grayscale conversion
 *
 * For simplicity, we'll use a simulated image represented as a 1D array of pixels,
 * where each pixel has R, G, B components (3 bytes per pixel).
 */

// Simulated image dimensions
constexpr int WIDTH = 1024;
constexpr int HEIGHT = 768;
constexpr int CHANNELS = 3;  // RGB
constexpr int IMAGE_SIZE = WIDTH * HEIGHT * CHANNELS;

// Utility function to initialize a test image
void initialize_test_image(uint8_t* image, int width, int height, int channels) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * channels;

            // Create a gradient pattern
            image[idx + 0] = static_cast<uint8_t>(x * 255 / width);  // R
            image[idx + 1] = static_cast<uint8_t>(y * 255 / height); // G
            image[idx + 2] = static_cast<uint8_t>(128);              // B
        }
    }
}

// Print a small section of the image for verification
void print_image_section(const uint8_t* image, int width, int channels,
                         int start_x, int start_y, int section_width, int section_height) {
    std::cout << "Image section (" << start_x << "," << start_y << ") to ("
              << start_x + section_width - 1 << "," << start_y + section_height - 1 << "):" << std::endl;

    for (int y = start_y; y < start_y + section_height; y++) {
        for (int x = start_x; x < start_x + section_width; x++) {
            int idx = (y * width + x) * channels;
            std::cout << "(" << static_cast<int>(image[idx + 0]) << ","
                      << static_cast<int>(image[idx + 1]) << ","
                      << static_cast<int>(image[idx + 2]) << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// 1. Brightness adjustment - Scalar implementation
void adjust_brightness_scalar(uint8_t* image, int size, int brightness) {
    for (int i = 0; i < size; i++) {
        int value = static_cast<int>(image[i]) + brightness;
        image[i] = static_cast<uint8_t>(std::min(255, std::max(0, value)));
    }
}

// 1. Brightness adjustment - SIMD implementation
// void adjust_brightness_simd(uint8_t* image, int size, int brightness) {
//     // Create a vector with the brightness value
//     __m256i brightness_vec = _mm256_set1_epi8(static_cast<char>(brightness));
//     __m256i zero_vec = _mm256_setzero_si256();
//     __m256i max_vec = _mm256_set1_epi8(static_cast<char>(255));

//     // Process 32 bytes at a time (32 pixels)
//     int i = 0;
//     for (; i <= size - 32; i += 32) {
//         // Load 32 bytes
//         __m256i pixels = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&image[i]));

//         // Add brightness
//         __m256i result = _mm256_adds_epu8(pixels, brightness_vec);

//         // Store result
//         _mm256_storeu_si256(reinterpret_cast<__m256i*>(&image[i]), result);
//     }

//     // Handle remaining pixels
//     for (; i < size; i++) {
//         int value = static_cast<int>(image[i]) + brightness;
//         image[i] = static_cast<uint8_t>(std::min(255, std::max(0, value)));
//     }
// }

// // 2. Contrast enhancement - Scalar implementation
// void enhance_contrast_scalar(uint8_t* image, int size, float contrast) {
//     // Apply contrast formula: (pixel - 128) * contrast + 128
//     for (int i = 0; i < size; i++) {
//         float value = (static_cast<float>(image[i]) - 128.0f) * contrast + 128.0f;
//         image[i] = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, value)));
//     }
// }

// 2. Contrast enhancement - SIMD implementation
// void enhance_contrast_simd(uint8_t* image, int size, float contrast) {
//     // We'll process 8 pixels at a time (converting to float for the calculation)
//     __m256 contrast_vec = _mm256_set1_ps(contrast);
//     __m256 offset_vec = _mm256_set1_ps(128.0f);
//     __m256 min_vec = _mm256_setzero_ps();
//     __m256 max_vec = _mm256_set1_ps(255.0f);

//     // Process 8 pixels at a time
//     int i = 0;
//     for (; i <= size - 8; i += 8) {
//         // Load 8 bytes and convert to float
//         __m128i pixels_epi8 = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(&image[i]));
//         __m256i pixels_epi32 = _mm256_cvtepu8_epi32(pixels_epi8);
//         __m256 pixels_ps = _mm256_cvtepi32_ps(pixels_epi32);

//         // Apply contrast formula: (pixel - 128) * contrast + 128
//         __m256 centered = _mm256_sub_ps(pixels_ps, offset_vec);
//         __m256 scaled = _mm256_mul_ps(centered, contrast_vec);
//         __m256 result_ps = _mm256_add_ps(scaled, offset_vec);

//         // Clamp to [0, 255]
//         result_ps = _mm256_min_ps(_mm256_max_ps(result_ps, min_vec), max_vec);

//         // Convert back to integers and store
//         __m256i result_epi32 = _mm256_cvtps_epi32(result_ps);
//         __m128i result_epi8 = _mm256_cvtepi32_epi8(result_epi32);
//         _mm_storel_epi64(reinterpret_cast<__m128i*>(&image[i]), result_epi8);
//     }

//     // Handle remaining pixels
//     for (; i < size; i++) {
//         float value = (static_cast<float>(image[i]) - 128.0f) * contrast + 128.0f;
//         image[i] = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, value)));
//     }
// }

// 3. Grayscale conversion - Scalar implementation
void convert_to_grayscale_scalar(const uint8_t* src, uint8_t* dst, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int src_idx = (y * width + x) * CHANNELS;
            int dst_idx = y * width + x;

            // Standard grayscale conversion weights
            uint8_t gray = static_cast<uint8_t>(
                0.299f * src[src_idx + 0] +  // R
                0.587f * src[src_idx + 1] +  // G
                0.114f * src[src_idx + 2]    // B
            );

            dst[dst_idx] = gray;
        }
    }
}

// 3. Grayscale conversion - SIMD implementation
void convert_to_grayscale_simd(const uint8_t* src, uint8_t* dst, int width, int height) {
    // RGB to Grayscale conversion weights
    const float weight_r = 0.299f;
    const float weight_g = 0.587f;
    const float weight_b = 0.114f;

    // Process 4 pixels at a time (4 pixels * 3 channels = 12 bytes)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 4) {
            // Handle edge case
            if (x + 4 > width) {
                // Fall back to scalar for the last few pixels
                for (int i = x; i < width; i++) {
                    int src_idx = (y * width + i) * 3;
                    float r = static_cast<float>(src[src_idx + 0]);
                    float g = static_cast<float>(src[src_idx + 1]);
                    float b = static_cast<float>(src[src_idx + 2]);

                    float gray = r * weight_r + g * weight_g + b * weight_b;
                    dst[y * width + i] = static_cast<uint8_t>(gray);
                }
                break;
            }

            // Process 4 pixels at once using AVX2
            __m128i pixel0 = _mm_set_epi32(0, src[(y * width + x + 0) * 3 + 2],
                                          src[(y * width + x + 0) * 3 + 1],
                                          src[(y * width + x + 0) * 3 + 0]);
            __m128i pixel1 = _mm_set_epi32(0, src[(y * width + x + 1) * 3 + 2],
                                          src[(y * width + x + 1) * 3 + 1],
                                          src[(y * width + x + 1) * 3 + 0]);
            __m128i pixel2 = _mm_set_epi32(0, src[(y * width + x + 2) * 3 + 2],
                                          src[(y * width + x + 2) * 3 + 1],
                                          src[(y * width + x + 2) * 3 + 0]);
            __m128i pixel3 = _mm_set_epi32(0, src[(y * width + x + 3) * 3 + 2],
                                          src[(y * width + x + 3) * 3 + 1],
                                          src[(y * width + x + 3) * 3 + 0]);

            // Convert to float for calculations
            __m128 pixel0_ps = _mm_cvtepi32_ps(pixel0);
            __m128 pixel1_ps = _mm_cvtepi32_ps(pixel1);
            __m128 pixel2_ps = _mm_cvtepi32_ps(pixel2);
            __m128 pixel3_ps = _mm_cvtepi32_ps(pixel3);

            // Apply weights
            __m128 weights = _mm_set_ps(0.0f, weight_b, weight_g, weight_r);

            // Dot product for each pixel
            __m128 gray0 = _mm_dp_ps(pixel0_ps, weights, 0x71);
            __m128 gray1 = _mm_dp_ps(pixel1_ps, weights, 0x71);
            __m128 gray2 = _mm_dp_ps(pixel2_ps, weights, 0x71);
            __m128 gray3 = _mm_dp_ps(pixel3_ps, weights, 0x71);

            // Convert back to integers
            __m128i gray0_epi32 = _mm_cvtps_epi32(gray0);
            __m128i gray1_epi32 = _mm_cvtps_epi32(gray1);
            __m128i gray2_epi32 = _mm_cvtps_epi32(gray2);
            __m128i gray3_epi32 = _mm_cvtps_epi32(gray3);

            // Extract the grayscale values
            dst[y * width + x + 0] = static_cast<uint8_t>(_mm_extract_epi32(gray0_epi32, 0));
            dst[y * width + x + 1] = static_cast<uint8_t>(_mm_extract_epi32(gray1_epi32, 0));
            dst[y * width + x + 2] = static_cast<uint8_t>(_mm_extract_epi32(gray2_epi32, 0));
            dst[y * width + x + 3] = static_cast<uint8_t>(_mm_extract_epi32(gray3_epi32, 0));
        }
    }
}

int main() {
  {
    std::cout << "=== INTEL SIMD Image Processing Example ===" << std::endl;

//     // Allocate memory for the test image
//     uint8_t* original_image = new uint8_t[IMAGE_SIZE];
//     uint8_t* processed_image = new uint8_t[IMAGE_SIZE];
//     uint8_t* grayscale_image = new uint8_t[WIDTH * HEIGHT];

//     // Initialize the test image
//     initialize_test_image(original_image, WIDTH, HEIGHT, CHANNELS);

//     // Print a small section of the original image
//     std::cout << "Original Image:" << std::endl;
//     print_image_section(original_image, WIDTH, CHANNELS, 0, 0, 3, 3);

//     // 1. Brightness Adjustment
//     std::cout << "1. Brightness Adjustment" << std::endl;

//     // Copy original image to processed image
//     std::copy(original_image, original_image + IMAGE_SIZE, processed_image);

//     // Benchmark brightness adjustment
//     auto brightness_scalar = [&]() {
//       adjust_brightness_scalar(processed_image, IMAGE_SIZE, 50);
//     };

 //    auto brightness_simd = [&]() {
//       // Reset the image before each test
//       std::copy(original_image, original_image + IMAGE_SIZE, processed_image);
//       adjust_brightness_simd(processed_image, IMAGE_SIZE, 50);
//     };

//     benchmark_comparison("Brightness Adjustment", brightness_scalar, brightness_simd, 100);

//     // Print a small section of the brightness-adjusted image
//     std::cout << "Brightness-adjusted Image:" << std::endl;
//     print_image_section(processed_image, WIDTH, CHANNELS, 0, 0, 3, 3);

//     // 2. Contrast Enhancement
//     std::cout << "2. Contrast Enhancement" << std::endl;

//     // Reset the processed image
//     std::copy(original_image, original_image + IMAGE_SIZE, processed_image);

//     // Benchmark contrast enhancement
//     auto contrast_scalar = [&]() {
//       enhance_contrast_scalar(processed_image, IMAGE_SIZE, 1.5f);
//     };

//     auto contrast_simd = [&]() {
//       // Reset the image before each test
//       std::copy(original_image, original_image + IMAGE_SIZE, processed_image);
//       enhance_contrast_simd(processed_image, IMAGE_SIZE, 1.5f);
//     };

//     benchmark_comparison("Contrast Enhancement", contrast_scalar, contrast_simd, 100);

//     // Print a small section of the contrast-enhanced image
//     std::cout << "Contrast-enhanced Image:" << std::endl;
//     print_image_section(processed_image, WIDTH, CHANNELS, 0, 0, 3, 3);

    // 3. Grayscale Conversion
//     std::cout << "3. Grayscale Conversion" << std::endl;

//     // Benchmark grayscale conversion
//     auto grayscale_scalar = [&]() {
//       convert_to_grayscale_scalar(original_image, grayscale_image, WIDTH, HEIGHT);
//     };

//     auto grayscale_simd = [&]() {
//       convert_to_grayscale_simd(original_image, grayscale_image, WIDTH, HEIGHT);
//     };

//     benchmark_comparison("Grayscale Conversion", grayscale_scalar, grayscale_simd, 100);

//     // Print a small section of the grayscale image
//     std::cout << "Grayscale Image (showing first few pixels):" << std::endl;
//     for (int y = 0; y < 3; y++) {
//       for (int x = 0; x < 3; x++) {
//         std::cout << static_cast<int>(grayscale_image[y * WIDTH + x]) << " ";
//       }
//       std::cout << std::endl;
//     }
//     std::cout << std::endl;

//     // Clean up
//     delete[] original_image;
//     delete[] processed_image;
//     delete[] grayscale_image;
  }
  {
    std::cout << "=== INTEL SIMD Image Processing Example ===" << std::endl;

    // Allocate memory for the test image
    using a_t = std::array<uint8_t, IMAGE_SIZE>;
//    using g_t = std::array<uint8_t, WIDTH * HEIGHT>;
    a_t original_image;
    a_t processed_image;
//    g_t grayscale_image;

    // Initialize the test image
    initialize_test_image(&original_image[0], WIDTH, HEIGHT, CHANNELS);

    // Print a small section of the original image
    std::cout << "Original Image:" << std::endl;
    print_image_section(&original_image[0], WIDTH, CHANNELS, 0, 0, 3, 3);

    // 1. Brightness Adjustment
    std::cout << "1. Brightness Adjustment" << std::endl;
    uint8_t brightness = 50;
    auto adjust_brightness = [brightness](auto e){return eve::add[eve::saturated](e, brightness); };
    eve::algo::transform_to(original_image, processed_image, adjust_brightness);

    // Print a small section of the brightness-adjusted image
    std::cout << "Brightness-adjusted Image:" << std::endl;
    print_image_section(&processed_image[0], WIDTH, CHANNELS, 0, 0, 3, 3);

    // 2. Contrast Enhancement
    std::cout << "2. Contrast Enhancement" << std::endl;
    float contrast = 1.5f;
    auto enhance_contrast = [contrast](auto e){
      auto v = eve::fma(eve::convert(e, eve::as<float>())-128, contrast, 128);
      return eve::convert(v, eve::as<std::uint8_t>());
    };
    eve::algo::transform_to(original_image, processed_image, enhance_contrast);

    std::cout << "Brightness-adjusted Image:" << std::endl;
    print_image_section(&processed_image[0], WIDTH, CHANNELS, 0, 0, 3, 3);
  }
  return 0;
}
