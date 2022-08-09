//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/max_scalar_size.hpp>

TTS_CASE( "Check max_scalar_size" )
{
  TTS_CONSTEXPR_EQUAL(sizeof(int),  eve::max_scalar_size_v<int>);
  TTS_CONSTEXPR_EQUAL(sizeof(std::int8_t), eve::max_scalar_size_v<std::int8_t>);
  TTS_CONSTEXPR_EQUAL(sizeof(std::int8_t), (eve::max_scalar_size_v<kumi::tuple<std::int8_t, std::int8_t>>));
  TTS_CONSTEXPR_EQUAL(sizeof(int),  (eve::max_scalar_size_v<kumi::tuple<
                                       int, kumi::tuple<std::int8_t, std::int8_t>>>));
};
