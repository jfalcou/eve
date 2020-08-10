//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check enumerating constructor for wide of logical"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  auto filler = [](auto i, auto) { return i % 3 ? true : false; };

  eve::logical<eve::wide<EVE_TYPE, T>> simd(filler);
  eve::logical<eve::wide<EVE_TYPE, T>> ref;

  for(std::size_t i = 0; i < T::value; ++i)
    ref.set(i, filler(i, T::value));

  TTS_EQUAL(simd, ref);
}
