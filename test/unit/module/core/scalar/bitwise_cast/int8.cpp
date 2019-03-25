//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <cstdint>
using Type = std::int8_t;
#include "bitwise_cast.hpp"
TTS_CASE("Check bitwise_cast return type")
{
  using ut_t = eve::detail::as_integer_t<Type, unsigned>;
  using it_t = eve::detail::as_integer_t<Type, signed>;
  TTS_EXPR_IS(eve::bitwise_cast<it_t>(Type()), it_t);
  TTS_EXPR_IS(eve::bitwise_cast<ut_t>(Type()), ut_t);
  TTS_EXPR_IS(eve::bitwise_cast<Type>(Type()), Type);
}
