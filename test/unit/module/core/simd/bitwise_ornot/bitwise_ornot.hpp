//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_ORNOT_HPP
#define BITWISE_ORNOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/simd/bitwise_ornot.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check bitwise_ornot behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  wide<Type,T>  lhs([](auto i, auto c) { return c-i; })
    , rhs([](auto i, auto  ) { return i+1; })
    , ref([](auto i, auto c) { return eve::bitwise_ornot(Type(c-i),Type(i+1)); });

  if constexpr(std::is_integral_v<Type>)
    TTS_EQUAL(ref, eve::bitwise_ornot(lhs,rhs));
  else
    TTS_IEEE_EQUAL(ref, eve::bitwise_ornot(lhs,rhs));
}

TTS_CASE_TPL( "Check bitwise_ornot behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  wide<Type,T>  lhs([](auto i, auto c) { return i%3; })
    , ref([](auto i, auto c) { return eve::bitwise_ornot( Type(i%3), Type(7) ); });

  TTS_EQUAL(ref, eve::bitwise_ornot(lhs,7));
}

TTS_CASE("Check bitwise_ornot with mixed types")
{
  using eve::wide;

  {
    wide<float, fixed<16>> lhs([](auto i, auto c) { return c - i; });
    wide<int32_t, fixed<16>> rhs([](auto i, auto) { return i; });
    wide<float, fixed<16>>  ref([](auto i, auto c) { return eve::bitwise_ornot(float(c - i), int32_t(i)); });

    TTS_IEEE_EQUAL(ref, eve::bitwise_ornot(lhs, rhs));
  }
  {
    wide<int32_t, fixed<16>> lhs([](auto i, auto c) { return int32_t(i % 3); }),
      ref([](auto i, auto c) { return eve::bitwise_ornot(int32_t(i % 3), -3.322f); });

    TTS_IEEE_EQUAL(ref, eve::bitwise_ornot(lhs, -3.322f));
  }
}

#endif
