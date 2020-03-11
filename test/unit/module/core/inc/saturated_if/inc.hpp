//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check conditional saturated_(eve::inc) return type")
{
  using eve::saturated_;

  TTS_EXPR_IS((saturated_(eve::inc[EVE_TYPE()])(EVE_TYPE()))                , (EVE_TYPE));
  TTS_EXPR_IS((saturated_(eve::inc[EVE_VALUE()])(EVE_TYPE()))               , (EVE_TYPE));
  TTS_EXPR_IS((saturated_(eve::inc[true])(EVE_TYPE()))                  , (EVE_TYPE));
  TTS_EXPR_IS((saturated_(eve::inc[eve::logical<EVE_TYPE>()])(EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((saturated_(eve::inc[eve::logical<EVE_VALUE>()])(EVE_TYPE())) , (EVE_TYPE));
}

TTS_CASE("Check conditional saturated_(eve::inc) behavior")
{
  using eve::saturated_;

  EVE_TYPE tv(2);
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

  // All basic TRUE
  TTS_EQUAL(saturated_(eve::inc[ 1 ])(eve::Valmax<EVE_TYPE>())     , eve::Valmax<EVE_TYPE>());
  TTS_EQUAL(saturated_(eve::inc[ 1.0 ])(eve::Valmax<EVE_TYPE>())   , eve::Valmax<EVE_TYPE>());
  TTS_EQUAL(saturated_(eve::inc[ true ])(eve::Valmax<EVE_TYPE>())  , eve::Valmax<EVE_TYPE>());
  TTS_EQUAL(saturated_(eve::inc[ t ])(eve::Valmax<EVE_TYPE>())     , eve::Valmax<EVE_TYPE>());

  // All basic FALSE
  TTS_EQUAL(saturated_(eve::inc[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated_(eve::inc[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated_(eve::inc[ false ])(tv) , tv);
  TTS_EQUAL(saturated_(eve::inc[ f ])(tv)     , tv);

  // Mixed case
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(saturated_(eve::inc[ m ])(tv) , eve::if_else(m,saturated_(eve::inc)(tv), tv) );
}
