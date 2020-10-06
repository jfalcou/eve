//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>

TTS_CASE("Check eve::saturated(eve::convert) return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  TTS_EXPR_IS(eve::saturated(eve::convert)(EVE_TYPE(), eve::as<float>()), target_t);
}

TTS_CASE("Check eve::saturated(eve::convert) behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif


  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<EVE_TYPE>()), eve::as<float>()), (eve::valmin(eve::as<target_t>())) );
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<EVE_TYPE>()), eve::as<float>()), (eve::valmax(eve::as<target_t>())) );
  }
  else
  {
    if constexpr(sizeof(EVE_VALUE)<=sizeof(float))
    {
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<EVE_TYPE>()), eve::as<float>()), static_cast<target_t>(eve::valmin(eve::as<EVE_VALUE>())) );
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<EVE_TYPE>()), eve::as<float>()), static_cast<target_t>(eve::valmax(eve::as<EVE_VALUE>())) );
    }
  }

  TTS_EQUAL(eve::saturated(eve::convert)((EVE_TYPE(0))          , eve::as<float>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((EVE_TYPE(42.69))      , eve::as<float>()), static_cast<target_t>(EVE_VALUE(42.69)) );
}
