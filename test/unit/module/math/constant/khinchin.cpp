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
// khinchin Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of khinchin", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::khinchin(as<T>()), T);
  TTS_EXPR_IS(eve::khinchin(as<v_t>()), v_t);
};
//==================================================================================================
// khinchin tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of khinchin on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::khinchin[eve::lower](eve::as<T>()) <=2.685452001065306445309714 );
    TTS_EXPECT(eve::khinchin[eve::upper](eve::as<T>()) >= 2.685452001065306445309714);
  }
  TTS_EQUAL(eve::khinchin(eve::as<T>()), T(2.685452001065306445309714));
};

//==================================================================================================
// khinchin  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of khinchin on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::khinchin[eve::lower](as<T>()), eve::khinchin[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked khinchin
//==================================================================================================
TTS_CASE_WITH("Check behavior of khinchin[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::khinchin[mask](eve::as(a0)), eve::if_else(mask, eve::khinchin(eve::as(a0)), eve::zero));
};
