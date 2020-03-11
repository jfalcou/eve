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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>


TTS_CASE("Check conditional saturated(eve::mul) return type")
{
  TTS_EXPR_IS( (eve::saturated_(eve::mul[ EVE_TYPE()              ])(EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::saturated_(eve::mul[ eve::logical<EVE_TYPE>()])(EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::saturated_(eve::mul[ true                ])(EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check conditional saturated(eve::mul) behavior")
{
  EVE_TYPE fv{eve::Valmax<EVE_TYPE>()};
  EVE_TYPE tv{3};
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  TTS_EQUAL(eve::saturated_(eve::mul[ 1 ])(tv, fv)    , eve::saturated_(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::mul[ 1.0 ])(tv, fv)  , eve::saturated_(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::mul[ true ])(tv, fv) , eve::saturated_(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::mul[ t ])(tv, fv)    , eve::saturated_(eve::mul)(tv,fv));

  TTS_EQUAL(eve::saturated_(eve::mul[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated_(eve::mul[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated_(eve::mul[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::mul[ f ])(tv, fv)    , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL ( eve::saturated_(eve::mul[ m ])(tv, fv),
                  eve::if_else(m, eve::saturated_(eve::mul)(tv,fv), tv)
                );

}
