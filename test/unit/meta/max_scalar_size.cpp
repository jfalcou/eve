//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/max_scalar_size.hpp>

TTS_CASE( "Check max_scalar_size" )
{
  TTS_CONSTEXPR_EQUAL(sizeof(int),  eve::max_scalar_size_v<int>);
  TTS_CONSTEXPR_EQUAL(sizeof(char), eve::max_scalar_size_v<char>);
  TTS_CONSTEXPR_EQUAL(sizeof(char), (eve::max_scalar_size_v<kumi::tuple<char, char>>));
  TTS_CONSTEXPR_EQUAL(sizeof(int),  (eve::max_scalar_size_v<kumi::tuple<
                                       int, kumi::tuple<char, char>>>));
};
