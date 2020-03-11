//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::oneminus return type")
{
  TTS_EXPR_IS(eve::oneminus[ EVE_VALUE(0)  ](EVE_TYPE(0))              , (EVE_TYPE));
  TTS_EXPR_IS(eve::oneminus[ (EVE_TYPE(0)) ](EVE_TYPE(0))              , (EVE_TYPE));
  TTS_EXPR_IS(eve::oneminus[ (eve::logical<EVE_TYPE>(0))](EVE_TYPE(0)) , (EVE_TYPE));
  TTS_EXPR_IS(eve::oneminus[ eve::logical<EVE_VALUE>(0) ](EVE_TYPE(0)) , (EVE_TYPE));
  TTS_EXPR_IS(eve::oneminus[ true ](EVE_TYPE(0))                   , (EVE_TYPE));
}

TTS_CASE("Check eve::oneminus behavior")
{
  EVE_TYPE tv(2);
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  TTS_EQUAL(eve::oneminus[ 1 ](tv)   , (EVE_TYPE(-1)));
  TTS_EQUAL(eve::oneminus[ 1.0 ](tv) , (EVE_TYPE(-1)));
  TTS_EQUAL(eve::oneminus[ true ](tv), (EVE_TYPE(-1)));
  TTS_EQUAL(eve::oneminus[ t ](tv)   , (EVE_TYPE(-1)));

  TTS_EQUAL(eve::oneminus[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::oneminus[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::oneminus[ false ](tv) , tv);
  TTS_EQUAL(eve::oneminus[ f ](tv)     , tv);

    // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::oneminus[ m ](tv), eve::if_else(m, (EVE_TYPE(-1)), tv) );
}
