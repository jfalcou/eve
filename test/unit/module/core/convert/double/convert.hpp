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
#include <eve/function/converter.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::convert return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<double, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = double;
#endif

  TTS_EXPR_IS(eve::convert(EVE_TYPE(), eve::as<double>()), target_t);
  TTS_EXPR_IS(eve::float64(EVE_TYPE()), target_t);
}

TTS_CASE("Check eve::convert behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<double, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = double;
#endif

  TTS_EQUAL(eve::convert(eve::valmin(eve::as<EVE_TYPE>()), eve::as<double>()), static_cast<target_t>(eve::valmin(eve::as<EVE_VALUE>())) );
  TTS_EQUAL(eve::convert((EVE_TYPE(0))          , eve::as<double>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((EVE_TYPE(42.69))      , eve::as<double>()), static_cast<target_t>(EVE_VALUE(42.69)) );
  TTS_EQUAL(eve::convert(eve::valmax(eve::as<EVE_TYPE>()), eve::as<double>()), static_cast<target_t>(eve::valmax(eve::as<EVE_VALUE>())) );
}
