//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE_TPL("Check saturated_(eve::dec[condition] return type", EVE_TYPE)
{
  using eve::saturated_;

  TTS_EXPR_IS( saturated_(eve::dec[ T() ])(T())              , T);
  TTS_EXPR_IS( saturated_(eve::dec[ eve::logical<T>() ])(T()), T);
  TTS_EXPR_IS( saturated_(eve::dec[ true ])(T())             , T);
}

TTS_CASE_TPL("Check saturated_(eve::dec[condition] behavior", EVE_TYPE)
{
  using eve::saturated_;

  T tv{2};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  // All basic TRUE
  TTS_EQUAL(saturated_(eve::dec[ 1 ])(tv)     , tv - 1);
  TTS_EQUAL(saturated_(eve::dec[ 1.0 ])(tv)   , tv - 1);
  TTS_EQUAL(saturated_(eve::dec[ true ])(tv)  , tv - 1);
  TTS_EQUAL(saturated_(eve::dec[ t ])(tv)     , tv - 1);

  // All basic FALSE
  TTS_EQUAL(saturated_(eve::dec[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated_(eve::dec[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated_(eve::dec[ false ])(tv) , tv);
  TTS_EQUAL(saturated_(eve::dec[ f ])(tv)     , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(saturated_(eve::dec[ m ])(tv) , eve::if_else(m,saturated_(eve::dec)(tv), tv) );
}
