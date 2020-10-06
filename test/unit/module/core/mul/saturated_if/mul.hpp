//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>

TTS_CASE("Check conditional saturated(eve::mul) return type")
{
  TTS_EXPR_IS( (eve::saturated(eve::mul[ EVE_TYPE()               ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::saturated(eve::mul[ eve::logical<EVE_TYPE>() ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
  TTS_EXPR_IS( (eve::saturated(eve::mul[ true                     ])(EVE_TYPE(), EVE_TYPE())), EVE_TYPE);
}

TTS_CASE("Check conditional saturated(eve::mul) behavior")
{
  EVE_TYPE fv{eve::valmax(eve::as<EVE_TYPE>())};
  EVE_TYPE tv{3};
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  TTS_EQUAL(eve::saturated(eve::mul[ 1 ])(tv, fv)    , eve::saturated(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::mul[ 1.0 ])(tv, fv)  , eve::saturated(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::mul[ true ])(tv, fv) , eve::saturated(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::mul[ t ])(tv, fv)    , eve::saturated(eve::mul)(tv,fv));

  TTS_EQUAL(eve::saturated(eve::mul[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated(eve::mul[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated(eve::mul[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::mul[ f ])(tv, fv)    , tv);

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

  TTS_EQUAL ( eve::saturated(eve::mul[ m ])(tv, fv)
            , eve::if_else(m, eve::saturated(eve::mul)(tv,fv), tv)
            );

}
