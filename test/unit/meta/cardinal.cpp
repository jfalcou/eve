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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <array>
#include <tuple>

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

TTS_CASE( "Check for scalar tuple-like type cardinals")
{
  TTS_TYPE_IS( (eve::cardinal_t<std::array<float,8>>) , eve::scalar_cardinal );
  TTS_EQUAL  ( (eve::cardinal_v<std::array<float,8>>) , 1 );
  TTS_TYPE_IS( (eve::cardinal_t<std::pair<double,char>>) , eve::scalar_cardinal );
  TTS_EQUAL  ( (eve::cardinal_v<std::pair<double,char>>) , 1 );
  TTS_TYPE_IS( (eve::cardinal_t<std::tuple<std::int8_t,std::int16_t,std::int32_t>>) , eve::scalar_cardinal );
  TTS_EQUAL  ( (eve::cardinal_v<std::tuple<std::int8_t,std::int16_t,std::int32_t>>) , 1 );
}

TTS_CASE( "Check for SIMD tuple-like type cardinals")
{
  using wf_4_t = eve::wide<float  , eve::fixed<4>>;
  using wd_4_t = eve::wide<double , eve::fixed<4>>;
  using wc_4_t = eve::wide<char   , eve::fixed<4>>;

  TTS_TYPE_IS( (eve::cardinal_t<std::array<wf_4_t,8>>), eve::fixed<4> );
  TTS_EQUAL  ( (eve::cardinal_v<std::array<wf_4_t,8>>), 4 );
  TTS_TYPE_IS( (eve::cardinal_t<std::pair<wd_4_t,wc_4_t>>), eve::fixed<4> );
  TTS_EQUAL  ( (eve::cardinal_v<std::pair<wd_4_t,wc_4_t>>), 4 );
  TTS_TYPE_IS( (eve::cardinal_t<std::tuple<wf_4_t,wd_4_t,wc_4_t>>), eve::fixed<4> );
  TTS_EQUAL  ( (eve::cardinal_v<std::tuple<wf_4_t,wd_4_t,wc_4_t>>), 4 );
}
