//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MAKE_HPP
#define MAKE_HPP

#include "test.hpp"
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;

TTS_CASE_TPL("Check enumerating constructor for wide of logical",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  auto filler = [](auto i, auto) { return i % 3 ? true : false; };

  wide<logical<Type>, T>              simd(filler);
  std::array<logical<Type>, T::value> ref;
  for(std::size_t i = 0; i < T::value; ++i) ref[ i ] = filler(i, T::value);

  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
}
/*
TTS_CASE( "Check enumerating constructor for wide of 1 element" )
{
  using eve::wide;

  wide<Type,fixed<1>> simd( 42 );
  std::array<Type,1> ref{ 42 };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check enumerating constructor for wide of 2 elements" )
{
  using eve::wide;

  wide<Type,eve::fixed<2>> simd( 42, 69 );
  std::array<Type,2> ref{ 42, 69 };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check enumerating constructor for wide of 4 elements" )
{
  using eve::wide;

  wide<Type,eve::fixed<4>> simd( 42, 69, 13, 37 );
  std::array<Type,4> ref{ 42, 69, 13, 37 };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check enumerating constructor for wide of 8 elements" )
{
  using eve::wide;

  wide<Type,eve::fixed<8>> simd( 4, 2, 6, 9, 1, 3, 3, 7 );
  std::array<Type,8> ref{ 4, 2, 6, 9, 1, 3, 3, 7 };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check enumerating constructor for wide of 16 elements" )
{
  using eve::wide;

  wide<Type,eve::fixed<16>> simd( 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7 );
  std::array<Type,16> ref{ 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7 };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check enumerating constructor for wide of 32 elements" )
{
  using eve::wide;

  wide<Type,eve::fixed<32>> simd( 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                                , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                                );
  std::array<Type,32> ref { 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check enumerating constructor for wide of 64 elements" )
{
  using eve::wide;

  wide<Type,eve::fixed<64>> simd( 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                                , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                                , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                                , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                                );
  std::array<Type,64> ref { 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          };

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}
*/

#endif
