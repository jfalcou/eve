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

// One Newton correction on sqrt leaves a relative residual of about u^2, u being float's unit
// roundoff, which is eight double ULP in the unit TTS counts. A thousand two hundred seeds reach
// exactly that, so twelve is the tightest bound with room for a rarer draw.
//
// NEON has no square root instruction below asimd, where eve builds one from a reciprocal estimate:
// the correction starts further from the truth and the residual grows with the square of that
// distance. The armv7 job measured 57, and its bound stays looser because nothing samples it here.
constexpr bool   sqrt_is_estimated  = (eve::current_api >= eve::neon) && !(eve::current_api >= eve::asimd);
constexpr double two_sqrt_tolerance = sqrt_is_estimated ? 128.0 : 12.0;

TTS_CASE_WITH("Check behavior of two_sqrt_approx(wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(+5., +1000.)

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
    TTS_ULP_EQUAL(eve::sqrt(da0), (da+de), two_sqrt_tolerance);
  }
};

TTS_CASE_WITH("Check behavior of two_sqrt_approx(scalar)",
              eve::test::scalar::ieee_reals_wf16,
              tts::randoms(+5., +1000.)
             )
  <typename T>(T a0)
{
  using eve::two_sqrt_approx;
  if constexpr(sizeof(eve::element_type_t<T>) <= 4)
  {
    auto [a, e] = eve::two_sqrt_approx(a0);
    auto da = eve::upgrade(a);
    auto de = eve::upgrade(e);
    auto da0 = eve::upgrade(a0);
    // a scalar sqrt goes through the cpu_ path everywhere, so it is correctly rounded on every target
    TTS_ULP_EQUAL(eve::sqrt(da0), (da+de), 12.0);
  }
  else
  {
    using ld_t = long double;
    auto [a, e] = eve::two_sqrt_approx(a0);
    ld_t da = ld_t(a);
    ld_t de = ld_t(e);
    ld_t da0 = ld_t(a0);
    TTS_LESS(double(std::abs(std::sqrt(da0) - (da+de))), 6.0e-32);
  }
};
