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
#include <eve/function/plus.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/sqr.hpp>

TTS_CASE("Check eve::convert return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  TTS_EXPR_IS(eve::convert(EVE_TYPE(), eve::as<float>()), target_t);
  TTS_EXPR_IS(eve::float32(EVE_TYPE())     , target_t);
}

TTS_CASE("Check eve::convert behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  TTS_EQUAL(eve::convert((EVE_TYPE(0))          , eve::as<float>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((EVE_TYPE(42.69))      , eve::as<float>()), static_cast<target_t>(EVE_VALUE(42.69)) );

  if constexpr(sizeof(EVE_VALUE)<=sizeof(float))
  {
    TTS_EQUAL(eve::convert(eve::valmin(eve::as<EVE_TYPE>()), eve::as<float>()), static_cast<target_t>(eve::valmin(eve::as<EVE_VALUE>())) );
    TTS_EQUAL(eve::convert(eve::valmax(eve::as<EVE_TYPE>()), eve::as<float>()), static_cast<target_t>(eve::valmax(eve::as<EVE_VALUE>())) );
  }
}

TTS_CASE("float32")
{
  TTS_EQUAL(eve::convert((EVE_TYPE(0))        , eve::as<float>()), eve::float32(EVE_TYPE(0)) );
  TTS_EQUAL(eve::convert((EVE_TYPE(42.69))    , eve::as<float>()), eve::float32(EVE_TYPE(42.69)));
  TTS_EQUAL(eve::convert(eve::sqr(EVE_TYPE(2)), eve::as<float>()), eve::float32(eve::sqr)(EVE_TYPE(2)));
}
