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
// quarter Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of quarter", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::quarter(as<T>()), T);
  TTS_EXPR_IS(eve::quarter(as<v_t>()), v_t);
};
//==================================================================================================
// quarter tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of quarter on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::quarter[eve::lower](eve::as<T>()) <= 0.25l);
    TTS_EXPECT(eve::quarter[eve::upper](eve::as<T>()) >= 0.25l); 
  }
  TTS_EQUAL(eve::quarter(eve::as<T>()), T(0.25l));
};

//==================================================================================================
// quarter  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of quarter on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::quarter[eve::lower](as<T>()), eve::quarter[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked quarter
//==================================================================================================
TTS_CASE_WITH("Check behavior of quarter[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::quarter[mask](eve::as(a0)), eve::if_else(mask, eve::quarter(eve::as(a0)), eve::zero));
};
