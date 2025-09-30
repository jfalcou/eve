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
TTS_CASE_TPL("Check return types of welford_variance", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using welford_variance_result_t = eve::detail::welford_variance_result<T>;

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::welford_variance(T(), T(), T()), welford_variance_result_t);
    TTS_EXPR_IS(eve::welford_variance(T(), v_t(), T()), welford_variance_result_t);
    TTS_EXPR_IS(eve::welford_variance(v_t(), T(), T()), welford_variance_result_t);
    TTS_EXPR_IS(eve::welford_variance(T(), T(), v_t()), welford_variance_result_t);
    TTS_EXPR_IS(eve::welford_variance(v_t(), v_t(), T()), welford_variance_result_t);
    TTS_EXPR_IS(eve::welford_variance(v_t(), T(), v_t()), welford_variance_result_t);

    TTS_EXPR_IS(eve::welford_variance(v_t(), v_t(), v_t()), eve::detail::welford_variance_result<v_t>);
  }
};

//==================================================================================================
//== welford_variance tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of welford_variance(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::welford_variance;
  TTS_ULP_EQUAL(welford_variance(a0, a1, a2),
                eve::variance(a0, a1, a2), 1.5);
};



TTS_CASE_WITH("Check behavior of welford_variance kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::welford_variance;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(welford_variance(a0, a1, a2), eve::downgrade(welford_variance[widen](a0, a1, a2).variance), 1.5);

};
