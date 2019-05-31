//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REC_HPP
#define REC_HPP

#include "test.hpp"
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <eve/function/rec.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check rec behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs ( [](auto i, auto c)
                      {
                        if constexpr( std::is_floating_point_v<Type>) return Type(i+1)/(1+(c/2));
                        else                                          return i+1;
                      }
                    );

  wide<Type, T> ref([&lhs](auto i, auto) { return eve::rec(lhs[i]); });

  TTS_ULP_EQUAL(ref, eve::rec(lhs),0.5);
}

TTS_CASE_TPL("Check rec[raw_] behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs ( [](auto i, auto c)
                      {
                        if constexpr( std::is_floating_point_v<Type>) return Type(i+1)/(c/2);
                        else                                          return i+1;
                      }
                    );

  wide<Type, T> ref([&lhs](auto i, auto) { return eve::rec[eve::raw_](lhs[i]); });

  TTS_RELATIVE_EQUAL(ref, eve::rec[eve::raw_](lhs), 1);
}

TTS_CASE_TPL("Check rec[pedantic_] behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs ( [](auto i, auto c)
                      {
                        if constexpr( std::is_floating_point_v<Type>) return Type(i)/(c/2);
                        else                                          return i;
                      }
                    );

  wide<Type, T> ref([&lhs](auto i, auto) { return eve::rec[eve::pedantic_](lhs[i]); });

  TTS_RELATIVE_EQUAL(ref, eve::rec[eve::pedantic_](lhs), 1);
}

#endif
