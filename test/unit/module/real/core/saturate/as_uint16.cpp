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
  TTS_EXPR_IS(eve::saturate(T(), eve::as<std::uint16_t>()), T);
};

EVE_TEST_TYPES( "Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EQUAL(eve::saturate(T(0)    , eve::as<std::uint16_t>() ), T(0)     );
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::uint16_t>() ), T(42.69) );

  if constexpr(eve::signed_value<T>)
  {
    using v_t = eve::element_type_t<T>;
    if constexpr(sizeof(v_t) <= sizeof(std::int16_t))
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint16_t>()), eve::valmax(eve::as<T>()) );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint16_t>()), T(eve::valmax(eve::as<std::uint16_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint16_t>()), T(eve::valmax(eve::as<std::uint16_t>())) );
  }
};
