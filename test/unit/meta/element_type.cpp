//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/element_type.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check for element_type")
{
  TTS_TYPE_IS( eve::element_type_t<bool>                          , bool);
  TTS_TYPE_IS( eve::element_type_t<int>                           , int);
  TTS_TYPE_IS((eve::element_type_t<eve::wide<int,eve::fixed<8>>>) , int);
  TTS_TYPE_IS((eve::element_type_t<eve::wide<int>>)               , int);
  TTS_TYPE_IS( eve::element_type_t<eve::logical<int>>             , eve::logical<int>);
  TTS_TYPE_IS( eve::element_type_t<eve::logical<eve::wide<int>>>  , eve::logical<int>);
}
