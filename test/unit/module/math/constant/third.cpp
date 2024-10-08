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
// third Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of third", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::third(as<T>()), T);
  TTS_EXPR_IS(eve::third(as<v_t>()), v_t);
};
//==================================================================================================
// third tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of third on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::third[eve::lower](eve::as<T>()) <= 1.0l/3);
    TTS_EXPECT(eve::third[eve::upper](eve::as<T>()) >= 1.0l/3); 
  }
  TTS_EQUAL(eve::third(eve::as<T>()), T(1.0l/3));
};

//==================================================================================================
// third  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of third on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::third[eve::lower](as<T>()), eve::third[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked third
//==================================================================================================
TTS_CASE_WITH("Check behavior of third[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::third[mask](eve::as(a0)), eve::if_else(mask, eve::third(eve::as(a0)), eve::zero));
};
