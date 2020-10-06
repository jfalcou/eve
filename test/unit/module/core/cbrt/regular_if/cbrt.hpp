//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>

TTS_CASE("Check eve::cbrt[condition] return type")
{
  TTS_EXPR_IS( eve::cbrt[ EVE_TYPE()              ](EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS( eve::cbrt[ eve::logical<EVE_TYPE>()](EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS( eve::cbrt[ true                    ](EVE_TYPE()) , EVE_TYPE);
}

TTS_CASE("Check eve::cbrt[condition] behavior")
{
  EVE_TYPE tv{2};
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(eve::cbrt[ 1 ](tv)     , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ 1.0 ](tv)   , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ true ](tv)  , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ t ](tv)     , eve::cbrt(tv));

  // All basic FALSE
  TTS_EQUAL(eve::cbrt[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::cbrt[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::cbrt[ false ](tv) , tv);
  TTS_EQUAL(eve::cbrt[ f ](tv)     , tv);

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

  TTS_EQUAL(eve::cbrt[ m ](tv) , eve::if_else(m,eve::cbrt(tv), tv) );
}
