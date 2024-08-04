//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>
#include <cmath>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of abel on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::abel(i_t(), T(), T()), T);
  TTS_EXPR_IS(eve::abel(wi_t(), T(), T()), T);
  TTS_EXPR_IS(eve::abel(i_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::abel(wi_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::abel(i_t(), T(), v_t()), T);
};

//==================================================================================================
//== abel tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of abel on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0),
                            tts::between(1.0, 10.0),
                            tts::as_integer(tts::ramp(0))))
<typename T, typename I>(T const& a0, T const& a1, I const&)
{
  using v_t =  eve::element_type_t<T>;
  auto std_abel = [](uint32_t n, auto x, auto a) ->v_t{ return x*std::pow(x-n*a, n-1); };
  for( unsigned int n = 1; n < 6; ++n )
  {
    TTS_ULP_EQUAL(eve::abel(n, a0, a1), map(std_abel, n, a0, a1), 1.5);
  }
};
