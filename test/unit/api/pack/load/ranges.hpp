//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef RANGES_HPP
#define RANGES_HPP

#include <eve/pack.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>
#include <list>

using eve::fixed;

TTS_CASE( "Check ctor from range for pack of 1 element" )
{
  using eve::pack;

  std::list<Type> ref{ 42 };
  {
    pack<Type,fixed<1>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<1>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE( "Check ctor from range for pack of 2 elements" )
{
  using eve::pack;

  std::list<Type> ref{ 42, 69 };
  {
    pack<Type,fixed<2>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<2>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE( "Check ctor from range for pack of 4 elements" )
{
  using eve::pack;

  std::list<Type> ref{ 42, 69, 13, 37 };
  {
    pack<Type,fixed<4>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<4>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE( "Check ctor from range for pack of 8 elements" )
{
  using eve::pack;

  std::list<Type> ref{ 4, 2, 6, 9, 1, 3, 3, 7 };
  {
    pack<Type,fixed<8>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<8>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE( "Check ctor from range for pack of 16 elements" )
{
  using eve::pack;

  std::list<Type> ref{ 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7 };
  {
    pack<Type,fixed<16>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<16>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE( "Check ctor from range for pack of 32 elements" )
{
  using eve::pack;

  std::list<Type> ref { 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                      , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                      };
  {
    pack<Type,fixed<32>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<32>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE( "Check ctor from range for pack of 64 elements" )
{
  using eve::pack;

  std::list<Type> ref { 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                      , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                      , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                      , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                      };
  {
    pack<Type,fixed<64>> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,fixed<64>> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

#endif
