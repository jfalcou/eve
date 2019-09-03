//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SPLAT_HPP
#define SPLAT_HPP

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <algorithm>

using eve::fixed;

auto const all_true  = [](auto e) { return e.value(); };
auto const all_false = [](auto e) { return !e.value(); };

TTS_CASE_TPL("Check splatting constructor for logical wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  eve::logical<eve::wide<Type, T>> from_bool_t{true};
  eve::logical<eve::wide<Type, T>> from_logical_t{eve::logical<Type>(true)};
  eve::logical<eve::wide<Type, T>> from_value_t{Type{123}};

  eve::logical<eve::wide<Type, T>> from_bool_f{false};
  eve::logical<eve::wide<Type, T>> from_logical_f{eve::logical<Type>(false)};
  eve::logical<eve::wide<Type, T>> from_value_f{Type{0}};

  TTS_EXPECT(std::all_of(from_bool_t.begin(), from_bool_t.end(), all_true));
  TTS_EXPECT(std::all_of(from_logical_t.begin(), from_logical_t.end(), all_true));
  TTS_EXPECT(std::all_of(from_value_t.begin(), from_value_t.end(), all_true));

  TTS_EXPECT(std::all_of(from_bool_f.begin(), from_bool_f.end(), all_false));
  TTS_EXPECT(std::all_of(from_logical_f.begin(), from_logical_f.end(), all_false));
  TTS_EXPECT(std::all_of(from_value_f.begin(), from_value_f.end(), all_false));
}

#endif
