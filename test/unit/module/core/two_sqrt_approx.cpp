//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <cmath>

#include <numeric>

//==================================================================================================
//== two_sqrt_approx tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of average(wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(0., +1000.)
                           )
             )
  <typename T>(T a0)
{
  using eve::two_sqrt_approx;
  if constexpr(sizeof(eve::element_type_t<T>) <= 4)
  {
    auto [a, e] = two_sqrt_approx(a0);
    auto da = eve::upgrade(a);
    auto de = eve::upgrade(e);
    auto da0 = eve::upgrade(a0);
    TTS_ULP_EQUAL(eve::sqrt(da0), (da+de), 20.0);
  }
};

TTS_CASE_WITH("Check behavior of average(wide)",
              eve::test::scalar::ieee_reals_wf16,
              tts::generate(tts::randoms(0., +1000.))
             )
  <typename T>(T a0)
{
  using eve::two_sqrt_approx;
  if constexpr(sizeof(eve::element_type_t<T>) <= 4)
  {
    auto [a, e] = two_sqrt_approx(a0);
    auto da = eve::upgrade(a);
    auto de = eve::upgrade(e);
    auto da0 = eve::upgrade(a0);
    TTS_ULP_EQUAL(eve::sqrt(da0), (da+de), 20.0);
  }
  else
  {
    using ld_t = long double;
    std::cout << sizeof(ld_t);
    auto [a, e] = two_sqrt_approx(a0);
    ld_t da = ld_t(a);
    ld_t de = ld_t(e);
    ld_t da0 = ld_t(a0);
    TTS_ULP_EQUAL(std::sqrtl(da0), (da+de), 20.0);
  }
};
