//==================================================================================================
/*
  Copyright 2020 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================

//! [threshold]
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include <eve/wide.hpp>

#include <eve/function/aligned_store.hpp>
#include <eve/function/deinterleave_first.hpp>
#include <eve/function/group.hpp>
#include <eve/function/if_zero_else_one.hpp>
#include <eve/function/is_less.hpp>
#include <eve/memory/allocator.hpp>

int main()
{
  namespace bs = eve;
  using namespace std::chrono;
  int image_size = 2560 * 2560;
  std::vector<std::int16_t, eve::allocator<std::int16_t>> image(image_size);
  std::vector<std::int8_t, eve::allocator<std::int8_t>> binary(image_size);
  std::generate(image.begin(), image.end(),
                []() { return std::rand() % std::numeric_limits<std::int16_t>::max(); });
  // select arbitrary threshold
  std::int16_t threshold = 5000;
  auto t0                = high_resolution_clock::now();
  //! [scalar-threshold]
  for (int i = 0; i < image.size(); ++i) {
    if (image[i] < threshold) {
      binary[i] = 0;
    } else {
      binary[i] = 1;
    }
  }
  auto t1 = high_resolution_clock::now();
  std::cout << "scalar       " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  //! [scalar-threshold]

  //! [simd-threshold]
  using wide_t = eve::wide<std::int16_t>;

  static const std::size_t cardinal = wide_t::static_size;

  //! [simd-threshold-downgrade]
  using wide_8           = eve::wide<std::int8_t>;
  std::size_t cardinal_8 = wide_8::static_size;
  std::vector<std::int8_t, eve::allocator<std::int8_t>> binary_8(image_size);
  t0 = high_resolution_clock::now();
  for (int i = 0; i < image.size(); i += cardinal_8) {
    wide_t v_image0(&image[i]);
    wide_t v_image1(&image[i + cardinal]);
    wide_t v_binary0      = eve::if_zero_else_one(eve::is_less(v_image0, threshold));
    wide_t v_binary1      = eve::if_zero_else_one(eve::is_less(v_image1, threshold));
    wide_8 v_binary_group = eve::group(v_binary0, v_binary1);
    eve::aligned_store(v_binary_group, &binary_8[i]);
  }
  t1 = high_resolution_clock::now();
  std::cout << "downgrade " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  //! [simd-threshold-downgrade]
}
// This code can be compiled using (for instance for gcc)
// g++ thresholding.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o thresholding
// -I/path_to/boost_simd/ -I/path_to/boost/

//! [threshold]
