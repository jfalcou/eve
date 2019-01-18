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

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/pack.hpp>
#include <eve/function/load.hpp>

using eve::fixed;

TTS_CASE_TPL( "load behavior for pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  TTS_SETUP("load a pack from")
  {
    using pack_t = eve::pack<Type,T>;
    auto filler = [](auto i, auto) { return Type(1)+i; };

    alignas(pack_t::static_alignment) std::array<Type, T::value> data;
    for(int i = 0; i < T::value; ++i)
      data[i] = filler(i,0);

    pack_t simd, ref(filler);

    TTS_SECTION("a pointer to pack")
    {
      simd = eve::load(&ref);
      TTS_EQUAL( simd, ref );
    }

    TTS_SECTION("an aligned pointer to pack")
    {
      simd = eve::load( eve::as_aligned<pack_t::static_alignment>(&ref) );
      TTS_EQUAL( simd, ref );
    }

    TTS_SECTION("a pointer to scalar values")
    {
      simd = eve::load(&data[0], eve::as(simd));
      TTS_EQUAL( simd, ref );
    }

    TTS_SECTION("an aligned pointer to scalar values")
    {
      simd = eve::load(eve::as_aligned<pack_t::static_alignment>(&data[0]), eve::as(simd));
      TTS_EQUAL( simd, ref );
    }
  }
}

TTS_CASE_TPL( "load behavior for pack of logical"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  TTS_SETUP("load a pack from")
  {
    using pack_t = eve::pack<eve::logical<Type>,T>;
    auto filler = [](auto i, auto) { return i% 3 ? true : false; };

    alignas(pack_t::static_alignment) std::array<eve::logical<Type>, T::value> data;
    for(std::size_t i = 0; i < T::value; ++i)
      data[i] = filler(i,0);

    pack_t simd, ref(filler);

    TTS_SECTION("a pointer to logical pack")
    {
      simd = eve::load(&ref);
      TTS_EQUAL( simd, ref );
    }

    TTS_SECTION("an aligned pointer to logical pack")
    {
      simd = eve::load( eve::as_aligned<pack_t::static_alignment>(&ref) );
      TTS_EQUAL( simd, ref );
    }

    TTS_SECTION("a pointer to scalar logical values")
    {
      simd = eve::load(&data[0], eve::as(simd));
      TTS_EQUAL( simd, ref );
    }

    TTS_SECTION("an aligned pointer to scalar logical values")
    {
      simd = eve::load(eve::as_aligned<pack_t::static_alignment>(&data[0]), eve::as(simd));
      TTS_EQUAL( simd, ref );
    }
  }
}

#endif
