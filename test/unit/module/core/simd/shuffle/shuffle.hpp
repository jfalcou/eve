//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SHUFFLE_HPP
#define SHUFFLE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check shuffle behavior",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using i_t = eve::detail::as_integer_t<Type>;

  wide<Type, T> arg([](auto i, auto) { return i; }),

}

#endif
