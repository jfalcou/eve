//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/cardinal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for scalar cardinals")
{
  TTS_TYPE_IS( eve::cardinal_t<float> , eve::scalar_cardinal );
  TTS_EQUAL  ( eve::cardinal_v<float>   , 1 );

  TTS_TYPE_IS( eve::cardinal_t<eve::logical<float>> , eve::scalar_cardinal );
  TTS_EQUAL  ( eve::cardinal_v<eve::logical<float>> , 1 );
}

TTS_CASE_TPL( "Check for wide cardinals"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            , eve::fixed<128>
            )
{
  TTS_TYPE_IS( (eve::cardinal_t< eve::wide<float, T> >), T        );
  TTS_EQUAL  ( (eve::cardinal_v< eve::wide<float, T> >), T::value );

  TTS_TYPE_IS( (eve::cardinal_t< eve::logical<eve::wide<float, T> >>), T        );
  TTS_EQUAL  ( (eve::cardinal_v< eve::logical<eve::wide<float, T> >>), T::value );
}
