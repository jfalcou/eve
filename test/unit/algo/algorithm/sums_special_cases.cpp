//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/reduce.hpp>
#include <eve/algo/zip.hpp>

#include <vector>

#if 0  // FIX-#880, FIX-#896"
TTS_CASE("eve.algo.reduce sum complex numbers")
{
  std::vector<float> real = { 0.0,  0.1,  0.2,  0.3 };
  std::vector<float> img  = { 0.0, -0.1, -0.2, -0.3 };

  using cmplx = kumi::tuple<float, float>;

  auto plus = [](eve::same_value_type<cmplx> auto x,
                 eve::same_value_type<cmplx> auto y) {
    get<0>(x) += get<0>(y);
    get<1>(x) += get<1>(y);
    return x;
  };


  auto [re, im] = eve::algo::reduce(
    eve::algo::zip(real, img),
    std::pair{plus, cmplx{0.0, 0.0} },
    cmplx{1, -1}
  );

  TTS_EQUAL(re,  1.6);
  TTS_EQUAL(im, -1.6);
}

#endif
