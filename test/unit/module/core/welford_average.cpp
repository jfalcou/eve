//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of average", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using welford_result_t = eve::detail::welford_result<T>;
  using v_t = eve::element_type_t<T>;
  // regular
  TTS_EXPR_IS(eve::welford_average(T(), T()), welford_result_t);
  TTS_EXPR_IS(eve::welford_average(T(), v_t()), welford_result_t);
  TTS_EXPR_IS(eve::welford_average(v_t(), T()), welford_result_t);
  TTS_EXPR_IS(eve::welford_average(v_t(), v_t()), eve::detail::welford_result<v_t>);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::welford_average(T(), T(), T()), welford_result_t);
    TTS_EXPR_IS(eve::welford_average(T(), v_t(), T()), welford_result_t);
    TTS_EXPR_IS(eve::welford_average(v_t(), T(), T()), welford_result_t);
    TTS_EXPR_IS(eve::welford_average(T(), T(), v_t()), welford_result_t);
    TTS_EXPR_IS(eve::welford_average(v_t(), v_t(), T()), welford_result_t);
    TTS_EXPR_IS(eve::welford_average(v_t(), T(), v_t()), welford_result_t);

    TTS_EXPR_IS(eve::welford_average(v_t(), v_t(), v_t()), eve::detail::welford_result<v_t>);
  }
};

//==================================================================================================
//== welford_average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of welford_average(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T  a0, T a1, T a2)
{

  using eve::widen;
  using eve::average;
  using eve::welford_average;
  using eve::kahan;
  using eve::as;
  TTS_ULP_EQUAL(welford_average(a0, a1).avg_, (a0+a1)/2, 15.0);
  TTS_ULP_EQUAL(welford_average(a0, a1, a2).avg_,(a0+a1+a2)/3, 15.0);
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
  {
    TTS_ULP_EQUAL(welford_average(a0, a1, a2).avg_, eve::downgrade(average[widen](a0, a1, a2)), 15.0);
    TTS_ULP_EQUAL(welford_average(a0, a1, a2).avg_, average[kahan](a0, a1, a2), 15.0);
  }
};
