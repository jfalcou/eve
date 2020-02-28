//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
//! [threshold]
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#include <chrono>

#include <eve/wide.hpp>

#include <eve/function/binarize.hpp>
#include <eve/function/store.hpp>
#include <eve/function/is_less.hpp>

int main()
{
  namespace chr = std::chrono;
  using hrc     = chr::high_resolution_clock;

  size_t image_size = 25600 * 25600;
  std::vector<std::int16_t> image(image_size);
  std::vector<std::int16_t> binary(image_size);
  std::generate(image.begin(), image.end(),
                []() { return std::rand() % std::numeric_limits<std::int16_t>::max(); });
  // select arbitrary threshold
  std::int16_t threshold = 5000;
  //! [scalar-threshold]
  auto t0 = hrc::now();
  for (size_t i = 0; i < image.size(); ++i) {
     binary[i] = image[i] <  threshold; 
  }
  auto t1 = hrc::now();
  std::cout << " scalar " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;
  //! [scalar-threshold]

  //! [simd-threshold]
  using wide_t    = eve::wide<std::int16_t>;

  t0 = hrc::now();
  wide_t v_threshold{threshold};
  for (size_t i = 0; i < image.size(); i += wide_t::static_size) {
    wide_t v_image(&image[i]);
    wide_t v_binary = eve::binarize(v_image < v_threshold);
    eve::store(v_binary, &binary[i]);
  }
  t1 = hrc::now();
  std::cout << " simd " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;
  //! [simd-threshold]
}
// This code can be compiled using (for instance for gcc)
// g++ thresholding.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o thresholding
// -I/path_to/eve/ 

//! [threshold]
