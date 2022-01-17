//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

EVE_TEST_TYPES( "Check eve::saturate return type", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS(eve::saturate(T(),   eve::as<double>()), T);
};

EVE_TEST_TYPES( "Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<double>()), eve::valmin(eve::as<T>()) );
  TTS_EQUAL(eve::saturate(T(0)            , eve::as<double>()), T(0)             );
  TTS_EQUAL(eve::saturate(T(42.69)        , eve::as<double>()), T(42.69)         );
  TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<double>()), eve::valmax(eve::as<T>()) );
};
