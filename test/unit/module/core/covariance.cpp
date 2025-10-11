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
TTS_CASE_TPL("Check return types of welford_covariance", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using welford_covariance_result_t = eve::detail::welford_covariance_result<T>;

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::welford_covariance(T(), T(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(T(), v_t(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), T(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(T(), T(), v_t(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), v_t(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), T(), v_t(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), v_t(), v_t()), eve::detail::welford_covariance_result<v_t>);
  }
};

//==================================================================================================
//== welford_covariance tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of welford_covariance(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::welford_covariance;
  TTS_ULP_EQUAL(welford_covariance(a0, a1, a2, a0, a1, a2).covariance,
                eve::variance(a0, a1, a2), 1.5);
};
