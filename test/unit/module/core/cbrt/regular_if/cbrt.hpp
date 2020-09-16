//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check eve::cbrt[condition] return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::cbrt[ T() ](T())               , T);
  TTS_EXPR_IS( eve::cbrt[ eve::logical<T>() ](T()) , T);
  TTS_EXPR_IS( eve::cbrt[ true ](T())              , T);
}

TTS_CASE_TPL("Check eve::cbrt[condition] behavior", EVE_TYPE)
{
  T tv{2};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(eve::cbrt[ 1 ](tv)     , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ 1.0 ](tv)   , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ true ](tv)  , eve::cbrt(tv));
  TTS_EQUAL(eve::cbrt[ t ](tv)     , eve::cbrt(tv));

  // All basic FALSE
  TTS_EQUAL(eve::cbrt[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::cbrt[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::cbrt[ false ](tv) , tv);
  TTS_EQUAL(eve::cbrt[ f ](tv)     , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::cbrt[ m ](tv) , eve::if_else(m,eve::cbrt(tv), tv) );
}
