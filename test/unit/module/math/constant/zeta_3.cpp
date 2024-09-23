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
// zeta_3 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of zeta_3", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::zeta_3(as<T>()), T);
  TTS_EXPR_IS(eve::zeta_3(as<v_t>()), v_t);
};
//==================================================================================================
// zeta_3 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of zeta_3 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::zeta_3[eve::lower](eve::as<T>()) <= 1.202056903159594285399738161511449990l);
    TTS_EXPECT(eve::zeta_3[eve::upper](eve::as<T>()) >= 1.202056903159594285399738161511449990l); 
  }
  TTS_EQUAL(eve::zeta_3(eve::as<T>()), T(1.202056903159594285399738161511449990l));
};

//==================================================================================================
// zeta_3  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of zeta_3 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::zeta_3[eve::lower](as<T>()), eve::zeta_3[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked zeta_3
//==================================================================================================
TTS_CASE_WITH("Check behavior of zeta_3[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::zeta_3[mask](eve::as(a0)), eve::if_else(mask, eve::zeta_3(eve::as(a0)), eve::zero));
};
