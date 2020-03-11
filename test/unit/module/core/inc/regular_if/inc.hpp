//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check conditional eve::inc return type")
{
  TTS_EXPR_IS((eve::inc[EVE_TYPE()](EVE_TYPE()))                , (EVE_TYPE));
  TTS_EXPR_IS((eve::inc[EVE_VALUE()](EVE_TYPE()))               , (EVE_TYPE));
  TTS_EXPR_IS((eve::inc[true](EVE_TYPE()))                  , (EVE_TYPE));
  TTS_EXPR_IS((eve::inc[eve::logical<EVE_TYPE>()](EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::inc[eve::logical<EVE_VALUE>()](EVE_TYPE())) , (EVE_TYPE));
}

TTS_CASE("Check conditional eve::inc behavior")
{
  EVE_TYPE tv(2);
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  // All basic TRUE
  TTS_EQUAL(eve::inc[ 1 ](tv)     , eve::inc(tv));
  TTS_EQUAL(eve::inc[ 1.0 ](tv)   , eve::inc(tv));
  TTS_EQUAL(eve::inc[ true ](tv)  , eve::inc(tv));
  TTS_EQUAL(eve::inc[ t ](tv)     , eve::inc(tv));

  // All basic FALSE
  TTS_EQUAL(eve::inc[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::inc[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::inc[ false ](tv) , tv);
  TTS_EQUAL(eve::inc[ f ](tv)     , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::inc[ m ](tv) , eve::if_else(m,eve::inc(tv), tv) );
}
