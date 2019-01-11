//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOAD_HPP
#define LOAD_HPP

#include <eve/pack.hpp>
#include <eve/logical.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>
#include <list>

using eve::fixed;
using eve::as_aligned;

using eve::fixed;

TTS_CASE_TPL( "Check ctor from unaligned pointer for pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;
  std::array<Type,T::value> ref;

  Type k = {};
  for(auto& e : ref) e = k++;

  pack<Type,T> simd( &ref[0] );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE_TPL( "Check ctor from unaligned pointer for logical pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;
  using eve::logical;

  std::array<logical<Type>,T::value> ref;

  logical<Type> k = true;
  for(auto& e : ref) e = (k = !k);

  pack<logical<Type>,T> simd( &ref[0] );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE_TPL( "Check ctor from aligned pointer for pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;
  constexpr auto algt = pack<Type,T>::static_alignment;

  alignas(algt) std::array<Type,T::value> ref;

  Type k = {};
  for(auto& e : ref) e = k++;

  pack<Type,T> simd( as_aligned<algt>(&ref[0]) );
  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE_TPL( "Check ctor from aligned pointer for logical pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;
  using eve::logical;
  constexpr auto algt = pack<Type,T>::static_alignment;

  alignas(algt) std::array<logical<Type>,T::value> ref;

  logical<Type> k = true;
  for(auto& e : ref) e = (k = !k);

  pack<logical<Type>,T> simd( as_aligned<algt>(&ref[0]) );
  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE_TPL( "Check ctor from range for pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;

  std::list<Type> ref(T::value);

  Type k = {};
  for(auto& e : ref) e = k++;

  {
    pack<Type,T> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<Type,T> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

TTS_CASE_TPL( "Check ctor from range for logical pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;
  using eve::logical;

  std::list<logical<Type>> ref(T::value);

  logical<Type> k = true;
  for(auto& e : ref) e = (k = !k);

  {
    pack<logical<Type>,T> simd( ref );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }

  {
    pack<logical<Type>,T> simd( ref.begin(), ref.end() );
    TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
  }
}

#endif
