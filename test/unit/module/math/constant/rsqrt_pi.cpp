//revised
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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of rsqrt_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::rsqrt_pi(as<T>()), T);
  TTS_EXPR_IS(eve::rsqrt_pi(as<v_t>()), v_t);
};
//==================================================================================================
// e  tests on scalar
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
// e  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of e on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::rsqrt_pi[eve::downward](as<T>())), eve::rsqrt_pi[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked rsqrt_pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of rsqrt_pi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::rsqrt_pi[mask](eve::as(a0)), eve::if_else(mask, eve::rsqrt_pi(eve::as(a0)), eve::zero));
};
