//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

using Type = float;
#include "is_not_equal_with_equal_nans.hpp"
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check is_not_equal behavior on nans",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  using t_t = wide<Type, T>;
  using l_t = eve::as_logical_t<t_t>;
  using eve::Nan;
  t_t v0([](auto i, auto) { return i % 3 ? Type(i) : Nan<Type>(); }),
      v1([](auto i, auto) { return i % 2 ? Type(i) : Nan<Type>(); });
  l_t ref([](auto i, auto c) {
    return eve::is_not_equal_with_equal_nans(i % 3 ? Type(i) : Nan<Type>(),
                                             i % 2 ? Type(i) : Nan<Type>());
  });

  TTS_EQUAL(ref, eve::is_not_equal_with_equal_nans(v0, v1));
  TTS_EQUAL(ref, eve::is_not_equal_with_equal_nans(v1, v0));
}
