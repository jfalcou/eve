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

TTS_CASE("Check conditional saturated(eve::div) return type")
{
  TTS_EXPR_IS( (eve::saturated(eve::div[ EVE_TYPE()               ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::saturated(eve::div[ eve::logical<EVE_TYPE>() ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::saturated(eve::div[ true                     ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check conditional saturated(eve::div) behavior")
{
  EVE_TYPE tv(eve::valmax(eve::as<EVE_TYPE>()));
  EVE_TYPE fv(3);
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  TTS_EQUAL(eve::saturated(eve::div[ 1 ])(tv, fv)    , eve::saturated(eve::div)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::div[ 1.0 ])(tv, fv)  , eve::saturated(eve::div)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::div[ true ])(tv, fv) , eve::saturated(eve::div)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::div[ t ])(tv, fv)    , eve::saturated(eve::div)(tv,fv));

  TTS_EQUAL(eve::saturated(eve::div[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated(eve::div[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated(eve::div[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::div[ f ])(tv, fv)    , tv);

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

  TTS_EQUAL ( eve::saturated(eve::div[ m ])(tv, fv),
                  eve::if_else(m, eve::saturated(eve::div)(tv,fv), tv)
                );
}
