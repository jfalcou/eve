//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/element_type.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for element_type")
{
  TTS_TYPE_IS( eve::element_type_t<bool>                          , bool);
  TTS_TYPE_IS( eve::element_type_t<int>                           , int);
  TTS_TYPE_IS((eve::element_type_t<eve::wide<int,eve::fixed<8>>>) , int);
  TTS_TYPE_IS((eve::element_type_t<eve::wide<int>>)               , int);
  TTS_TYPE_IS( eve::element_type_t<eve::logical<int>>             , eve::logical<int>);
  TTS_TYPE_IS( eve::element_type_t<eve::logical<eve::wide<int>>>  , eve::logical<int>);
}
