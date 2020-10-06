//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE("Check eve::div[condition] return type")
{
  TTS_EXPR_IS( (eve::div[ EVE_TYPE()              ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::div[ eve::logical<EVE_TYPE>()](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::div[ true                    ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check eve::div[condition] behavior")
{
  EVE_TYPE tv(2);
  EVE_TYPE fv(3);
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(eve::div[ 1 ](tv, fv)     , tv / fv);
  TTS_EQUAL(eve::div[ 1.0 ](tv, fv)   , tv / fv);
  TTS_EQUAL(eve::div[ true ](tv, fv)  , tv / fv);
  TTS_EQUAL(eve::div[ t ](tv, fv)     , tv / fv);

  // All basic FALSE
  TTS_EQUAL(eve::div[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::div[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::div[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::div[ f ](tv, fv)     , tv);

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

  TTS_EQUAL(eve::div[ m ](tv, fv) , eve::if_else(m,eve::div(tv, fv), tv) );
}
