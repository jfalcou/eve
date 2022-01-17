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
  TTS_EXPR_IS(eve::saturate(T(), eve::as<std::int8_t>()), T);
};

EVE_TEST_TYPES( "Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int8_t>()), T(eve::valmin(eve::as<std::int8_t>())) );
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int8_t>()), T(0) );
  }

  TTS_EQUAL(eve::saturate(T(0)    , eve::as<std::int8_t>()), T(0)     );
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::int8_t>()), T(42.69) );
  TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::int8_t>()), T(eve::valmax(eve::as<std::int8_t>())) );
};
