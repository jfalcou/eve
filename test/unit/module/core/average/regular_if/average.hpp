//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <eve/function/if_else.hpp>

TTS_CASE("Check eve::average[condition] return type")
{
  TTS_EXPR_IS( (eve::average[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::average[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::average[ true ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::average[ eve::if_(true)](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check eve::average[condition] behavior")
{
  EVE_TYPE tv{2};
  EVE_TYPE fv{3};
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(eve::average[ 1 ](tv, fv)     , eve::average(fv,tv));
  TTS_EQUAL(eve::average[ 1.0 ](tv, fv)   , eve::average(fv,tv));
  TTS_EQUAL(eve::average[ true ](tv, fv)  , eve::average(fv,tv));
  TTS_EQUAL(eve::average[ t ](tv, fv)     , eve::average(fv,tv));

  // All basic FALSE
  TTS_EQUAL(eve::average[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::average[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::average[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::average[ f ](tv, fv)     , tv);

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

  TTS_EQUAL(eve::average[ m ](tv, fv) , eve::if_else(m, eve::average(tv, fv), tv) );
}
