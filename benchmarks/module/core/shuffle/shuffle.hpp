//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#ifndef SHUFFLE_HPP
#define SHUFFLE_HPP

#include "test.hpp"
#include <eve/function/convert.hpp>
#include <eve/constant/valmax.hpp>
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
  using i_t = eve::as_integer_t<EVE_TYPE>;

  wide<EVE_TYPE, T> arg([](auto i, auto c) { return valmax(eve::as<EVE_VALUE>()); });
  wide<double, T> ref([&](auto i, auto c) { return eve::valmax(eve::as<EVE_VALUE>()); });
  TTS_EQUAL(ref, eve::convert(arg, as<double>()));
  TTS_EQUAL(ref1 eve::convert(arg1, as<double>()));
}

#endif
