//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#include <boost/math/special_functions/laguerre.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of laguerre on wide", eve::test::simd::ieee_reals

)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::laguerre(i_t(), T()), T);
  TTS_EXPR_IS(eve::laguerre(wi_t(), T()), T);
  TTS_EXPR_IS(eve::laguerre(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::laguerre(wi_t(), v_t()), T);
};

//==================================================================================================
//== laguerre tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of laguerre on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1, 1), tts::as_integer(tts::ramp(0))))
<typename T, typename I>(T const& a0, I const& i0)
{
  using v_t           = eve::element_type_t<T>;
  auto eve__laguerrev = [](auto n, auto x) { return eve::laguerre(n, x); };
  for( unsigned int n = 0; n < 5; ++n )
  {
    auto boost_laguerre = [&](auto i, auto) { return boost::math::laguerre(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__laguerrev(n, a0), T(boost_laguerre), 1024);
  }
  auto boost_laguerrev = [&](auto i, auto) { return boost::math::laguerre(i0.get(i), a0.get(i)); };
  TTS_RELATIVE_EQUAL(eve__laguerrev(i0, a0), T(boost_laguerrev), 0.01);
  for( unsigned int j = 0; j < eve::cardinal_v<T>; ++j )
  {
    auto boost_laguerre2 = [&](auto i, auto)
    { return boost::math::laguerre(i0.get(i), a0.get(j)); };
    TTS_RELATIVE_EQUAL(eve__laguerrev(i0, a0.get(j)), T(boost_laguerre2), 0.01);
  }
  for( unsigned int j = 0; j < eve::cardinal_v<T>; ++j )
  {
    for( unsigned int n = 0; n < eve::cardinal_v<T>; ++n )
    {
      TTS_RELATIVE_EQUAL(eve__laguerrev(i0.get(j), a0.get(n)),
                         v_t(boost::math::laguerre(i0.get(j), a0.get(n))),
                         0.01);
    }
  }
};
