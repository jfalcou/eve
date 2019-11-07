//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/convert.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check convert behavior when casting to double",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::as;
  using eve::wide;

  wide<Type, T> arg([](auto i, auto c) { return i+1; });
  wide<double, T> ref([&](auto i, auto c) { return static_cast<double>(arg[i]); });

  wide<Type, T> arg([](auto i, auto c) { return Valmax<Value>(); });
  wide<double, T> ref([&](auto i, auto c) { return eve::Valmax<Value>(); });
  TTS_EQUAL(ref, eve::convert(arg, as<double>()));
  TTS_EQUAL(ref1 eve::convert(arg1, as<double>())); 
}
