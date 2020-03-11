//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE("Check eve::add[condition] return type")
{
  TTS_EXPR_IS( (eve::add[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::add[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::add[ true ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check eve::add[condition] behavior")
{
  EVE_TYPE tv{2};
  EVE_TYPE fv{3};
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  // All basic TRUE
  TTS_EQUAL(eve::add[ 1 ](tv, fv)     , tv + fv);
  TTS_EQUAL(eve::add[ 1.0 ](tv, fv)   , tv + fv);
  TTS_EQUAL(eve::add[ true ](tv, fv)  , tv + fv);
  TTS_EQUAL(eve::add[ t ](tv, fv)     , tv + fv);

  // All basic FALSE
  TTS_EQUAL(eve::add[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::add[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::add[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::add[ f ](tv, fv)     , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::add[ m ](tv, fv) , eve::if_else(m,tv + fv, tv) );
}
