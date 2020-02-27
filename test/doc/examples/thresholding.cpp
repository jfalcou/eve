//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================

//! [threshold]
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include <eve/wide.hpp>

#include <eve/function/aligned_store.hpp>
#include <eve/function/group.hpp>
#include <eve/function/if_zero_else_one.hpp>
#include <eve/function/is_less.hpp>
#include <eve/memory/allocator.hpp>

int main()
{
  namespace bs   = eve;
  int image_size = 2560 * 2560;
  std::vector<std::int16_t, eve::allocator<std::int16_t>> image(image_size);
  std::vector<std::int16_t, eve::allocator<std::int16_t>> binary(image_size);
  std::generate(image.begin(), image.end(),
                []() { return std::rand() % std::numeric_limits<std::int16_t>::max(); });
  // select arbitrary threshold
  std::int16_t threshold = 5000;
  //! [scalar-threshold]
  for (int i = 0; i < image.size(); ++i) {
    if (image[i] < threshold) {
      binary[i] = 0;
    } else {
      binary[i] = 1;
    }
  }
  //! [scalar-threshold]

  //! [simd-threshold]
  using wide_t    = eve::wide<std::int16_t>;
  using logical_t = eve::wide<eve::logical<std::int16_t>>;

  wide_t v_threshold{threshold};
  for (int i = 0; i < image.size(); i += wide_t::static_size) {
    wide_t v_image(&image[i]);
    logical_t v_res = eve::is_less(v_image, v_threshold);
    wide_t v_binary = eve::if_zero_else_one(v_res);
    eve::aligned_store(v_binary, &binary[i]);
  }
  //! [simd-threshold]
}
// This code can be compiled using (for instance for gcc)
// g++ thresholding.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o thresholding
// -I/path_to/boost_simd/ -I/path_to/boost/

//! [threshold]
