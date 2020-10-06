//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check eve::dec[condition] return type")
{
  TTS_EXPR_IS( eve::dec[ EVE_TYPE()               ](EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS( eve::dec[ eve::logical<EVE_TYPE>() ](EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS( eve::dec[ true                     ](EVE_TYPE()) , EVE_TYPE);
}

TTS_CASE("Check eve::dec[condition] behavior")
{
  EVE_TYPE tv(2);
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(eve::dec[ 1 ](tv)     , eve::dec(tv));
  TTS_EQUAL(eve::dec[ 1.0 ](tv)   , eve::dec(tv));
  TTS_EQUAL(eve::dec[ true ](tv)  , eve::dec(tv));
  TTS_EQUAL(eve::dec[ t ](tv)     , eve::dec(tv));

  // All basic FALSE
  TTS_EQUAL(eve::dec[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::dec[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::dec[ false ](tv) , tv);
  TTS_EQUAL(eve::dec[ f ](tv)     , tv);

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

  TTS_EQUAL(eve::dec[ m ](tv) , eve::if_else(m,eve::dec(tv), tv) );
}
