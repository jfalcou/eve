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
TTS_CASE("Check eve::mul[condition] return type")
{
  TTS_EXPR_IS( (eve::mul[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::mul[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::mul[ true ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check eve::mul[condition] behavior")
{
  EVE_TYPE tv{2};
  EVE_TYPE fv{3};
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  // All basic TRUE
  TTS_EQUAL(eve::mul[ 1 ](tv, fv)     , tv * fv);
  TTS_EQUAL(eve::mul[ 1.0 ](tv, fv)   , tv * fv);
  TTS_EQUAL(eve::mul[ true ](tv, fv)  , tv * fv);
  TTS_EQUAL(eve::mul[ t ](tv, fv)     , tv * fv);

  // All basic FALSE
  TTS_EQUAL(eve::mul[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::mul[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::mul[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::mul[ f ](tv, fv)     , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::mul[ m ](tv, fv) , eve::if_else(m,tv * fv, tv) );
}
