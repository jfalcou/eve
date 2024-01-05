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
TTS_CASE_TPL("Check return types of euler", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::euler(as<T>()), T);
  TTS_EXPR_IS(eve::euler(as<v_t>()), v_t);
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
    TTS_EXPECT(eve::euler[eve::downward](as<elt_t>()) < std::exp(1.0l));
    TTS_EXPECT(eve::euler[eve::upward](as<elt_t>()) > std::exp(1.0l));
   }
  TTS_EQUAL(eve::euler(as<T>()), T(std::exp(1.0l)));
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
  TTS_EXPECT(eve::all(eve::test::is_near(eve::euler[eve::downward](as<T>()), eve::euler[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked euler
//==================================================================================================
TTS_CASE_WITH("Check behavior of euler[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::euler[mask](eve::as(a0)), eve::if_else(mask, eve::euler(eve::as(a0)), eve::zero));
};
