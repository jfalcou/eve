//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_NOT_HPP
#define LOGICAL_NOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_not behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t = eve::wide<Type, T>;
  using l_t = eve::as_logical_t <t_t>;

  l_t lhs([](auto i, auto) { return i%2 == 0; });
  l_t ref([](auto i, auto) { return eve::logical_not(i%2 == 0); });

  TTS_EQUAL(ref, eve::logical_not(lhs));
  TTS_EQUAL(ref, !lhs);
}


#endif
