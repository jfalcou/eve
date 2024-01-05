//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sqrt_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrt_2(as<T>()), T);
  TTS_EXPR_IS(eve::sqrt_2(as<v_t>()), v_t);
};
//==================================================================================================
// e  tests on scalar on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of e on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::rsqrt_pi[eve::downward](as<elt_t>())
               < 0.564189583547756286948079451560772585844050629329l);
    TTS_EXPECT(eve::rsqrt_pi[eve::upward](as<elt_t>())
               > 0.564189583547756286948079451560772585844050629329l);
  }
  TTS_EQUAL(eve::rsqrt_pi(as<T>()), T(0.564189583547756286948079451560772585844050629329l));
};

//==================================================================================================
// e  tests on wide on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of e on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::sqrt_2[eve::downward](as<T>()), eve::sqrt_2[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked sqrt_2
//==================================================================================================
TTS_CASE_WITH("Check behavior of sqrt_2[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sqrt_2[mask](eve::as(a0)), eve::if_else(mask, eve::sqrt_2(eve::as(a0)), eve::zero));
};
