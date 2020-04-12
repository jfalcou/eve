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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
TTS_CASE("Check eve::div[condition] return type")
{
  TTS_EXPR_IS( (eve::div[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::div[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::div[ true ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check eve::div[condition] behavior")
{
  EVE_TYPE tv{2};
  EVE_TYPE fv{3};
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

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
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::div[ m ](tv, fv) , eve::if_else(m,eve::div(tv, fv), tv) );
}
