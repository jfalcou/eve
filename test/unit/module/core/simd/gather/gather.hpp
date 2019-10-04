//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef GATHER_HPP
#define GATHER_HPP

#include <eve/function/gather.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL( "Check gather behavior with int32 indexes",
              fixed<1>,
              fixed<2>,
              fixed<4>,
              fixed<8>,
              fixed<16>,
              fixed<32>,
              fixed<64>
            )
{
  using eve::wide;

  Type data[T::value];
  for(std::size_t i = 0;i<T::value;++i) data[i] = Type(1) + i;

  wide<std::int32_t, T> maps([](auto i, auto c) { return i%3 ? 1+i : c-i-1; });
  wide<Type,T> ref( [&](auto i, auto) { return data[maps[i]]; } );

  TTS_EQUAL( ref, eve::gather(&data[0], maps) );
}

#endif
