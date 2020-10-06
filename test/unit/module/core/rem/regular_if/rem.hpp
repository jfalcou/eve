//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE("Check eve::rem[condition] return type")
{
  TTS_EXPR_IS( (eve::rem[ EVE_TYPE()              ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::rem[ eve::logical<EVE_TYPE>()](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::rem[ true                    ](EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check eve::rem[condition] behavior")
{
  EVE_TYPE tv(2);
  EVE_TYPE fv(3);
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  // All basic TRUE
  TTS_EQUAL(eve::rem[ 1 ](tv, fv)     , eve::toward_zero(eve::rem)(tv, fv));
  TTS_EQUAL(eve::rem[ 1.0 ](tv, fv)   , eve::toward_zero(eve::rem)(tv, fv));
  TTS_EQUAL(eve::rem[ true ](tv, fv)  , eve::toward_zero(eve::rem)(tv, fv));
  TTS_EQUAL(eve::rem[ t ](tv, fv)     , eve::toward_zero(eve::rem)(tv, fv));

  // All basic FALSE
  TTS_EQUAL(eve::rem[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::rem[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::rem[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::rem[ f ](tv, fv)     , tv);

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

  TTS_EQUAL(eve::rem[ m ](tv, fv) , eve::if_else(m,eve::toward_zero(eve::rem)(tv, fv), tv) );
}
