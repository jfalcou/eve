//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check conditional saturated(eve::inc) return type")
{
  using eve::saturated;

  TTS_EXPR_IS((saturated(eve::inc[EVE_TYPE()])(EVE_TYPE()))                , EVE_TYPE);
  TTS_EXPR_IS((saturated(eve::inc[EVE_VALUE()])(EVE_TYPE()))              , EVE_TYPE);
  TTS_EXPR_IS((saturated(eve::inc[true])(EVE_TYPE()))               , EVE_TYPE);
  TTS_EXPR_IS((saturated(eve::inc[eve::logical<EVE_TYPE>()])(EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((saturated(eve::inc[eve::logical<EVE_VALUE>()])(EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check conditional saturated(eve::inc) behavior")
{
  using eve::saturated;

  EVE_TYPE tv(2);
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(saturated(eve::inc[ 1 ])(eve::valmax(eve::as<EVE_TYPE>()))     , eve::valmax(eve::as<EVE_TYPE>()));
  TTS_EQUAL(saturated(eve::inc[ 1.0 ])(eve::valmax(eve::as<EVE_TYPE>()))   , eve::valmax(eve::as<EVE_TYPE>()));
  TTS_EQUAL(saturated(eve::inc[ true ])(eve::valmax(eve::as<EVE_TYPE>()))  , eve::valmax(eve::as<EVE_TYPE>()));
  TTS_EQUAL(saturated(eve::inc[ t ])(eve::valmax(eve::as<EVE_TYPE>()))     , eve::valmax(eve::as<EVE_TYPE>()));

  // All basic FALSE
  TTS_EQUAL(saturated(eve::inc[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated(eve::inc[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated(eve::inc[ false ])(tv) , tv);
  TTS_EQUAL(saturated(eve::inc[ f ])(tv)     , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  bool k = true;
  #if defined(EVE_SIMD_TESTS)
  for(std::size_t i=0;i<EVE_CARDINAL;++i)
  {
    m.set(i, k);
    k = !k;
  }
  #else
  m = k;
  #endif

  TTS_EQUAL(saturated(eve::inc[ m ])(tv) , eve::if_else(m,saturated(eve::inc)(tv), tv) );
}
