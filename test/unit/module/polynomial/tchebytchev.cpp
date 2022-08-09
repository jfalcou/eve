//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#include <boost/math/special_functions/chebyshev.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of tchebytchev on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::tchebytchev(i_t(), T()), T);
  TTS_EXPR_IS(eve::tchebytchev(wi_t(), T()), T);
  TTS_EXPR_IS(eve::tchebytchev(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::tchebytchev(wi_t(), v_t()), T);

  using eve::kind_1;
  TTS_EXPR_IS(kind_1(eve::tchebytchev)(i_t(), T()), T);
  TTS_EXPR_IS(kind_1(eve::tchebytchev)(wi_t(), T()), T);
  TTS_EXPR_IS(kind_1(eve::tchebytchev)(i_t(), v_t()), v_t);
  TTS_EXPR_IS(kind_1(eve::tchebytchev)(wi_t(), v_t()), T);

  using eve::kind_2;
  TTS_EXPR_IS(kind_2(eve::tchebytchev)(i_t(), T()), T);
  TTS_EXPR_IS(kind_2(eve::tchebytchev)(wi_t(), T()), T);
  TTS_EXPR_IS(kind_2(eve::tchebytchev)(i_t(), v_t()), v_t);
  TTS_EXPR_IS(kind_2(eve::tchebytchev)(wi_t(), v_t()), T);
};

//==================================================================================================
//== tchebytchev tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of tchebytchev on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0),
                            tts::between(1.0, 10.0),
                            tts::as_integer(tts::ramp(0))))
<typename T, typename I>(T const& a0, T const& a1, I const&)
{
  auto eve__tchebytchev = [](uint32_t n, auto x) { return eve::tchebytchev(n, x); };
  for( unsigned int n = 0; n < 6; ++n )
  {
    auto boost_tchebytchev = [&](auto i, auto e)
    { return boost::math::chebyshev_t((unsigned int)i, e); };
    TTS_ULP_EQUAL(eve__tchebytchev(n, a0), map(boost_tchebytchev, n, a0), 320);
    TTS_ULP_EQUAL(eve__tchebytchev(n, a1), map(boost_tchebytchev, n, a1), 320);
  }
};

TTS_CASE_WITH("Check behavior of successor(tchebytchev)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T const& a0)
{
  auto t3 = eve::tchebytchev(3, a0);
  auto t4 = eve::tchebytchev(4, a0);
  auto t5 = eve::tchebytchev(5, a0);
  TTS_ULP_EQUAL(eve::successor(eve::tchebytchev)(a0, t4, t3), t5, 64);
  using eve::kind_2;
  auto u3 = kind_2(eve::tchebytchev)(3, a0);
  auto u4 = kind_2(eve::tchebytchev)(4, a0);
  auto u5 = kind_2(eve::tchebytchev)(5, a0);
  TTS_ULP_EQUAL(eve::successor(eve::tchebytchev)(a0, u4, u3), u5, 300);
};
