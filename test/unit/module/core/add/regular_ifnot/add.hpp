//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE("Check eve::add.not_[condition] return type")
{
  TTS_EXPR_IS( (eve::add.not_[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::add.not_[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::add.not_[ true ](EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check eve::add.not_[condition] behavior")
{
  EVE_TYPE tv{2};
  EVE_TYPE fv{3};
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  // All basic TRUE
  TTS_EQUAL(eve::add.not_[ 1 ](tv, fv)     , tv);
  TTS_EQUAL(eve::add.not_[ 1.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::add.not_[ true ](tv, fv)  , tv);
  TTS_EQUAL(eve::add.not_[ t ](tv, fv)     , tv);

  // All basic FALSE
  TTS_EQUAL(eve::add.not_[ 0 ](tv, fv)     , tv + fv);
  TTS_EQUAL(eve::add.not_[ 0.0 ](tv, fv)   , tv + fv);
  TTS_EQUAL(eve::add.not_[ false ](tv, fv) , tv + fv);
  TTS_EQUAL(eve::add.not_[ f ](tv, fv)     , tv + fv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::add.not_[ m ](tv, fv) , eve::if_else(m,tv, tv + fv) );
}
