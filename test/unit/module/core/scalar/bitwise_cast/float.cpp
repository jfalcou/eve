//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

using Type = float;
#include "bitwise_cast.hpp"
TTS_CASE("Check bitwise_cast return type")
{
  using ut_t = eve::detail::as_integer_t<float, unsigned>;
  using it_t = eve::detail::as_integer_t<float, signed>;
  TTS_EXPR_IS(eve::bitwise_cast<it_t>(float()), it_t);
  TTS_EXPR_IS(eve::bitwise_cast<ut_t>(float()), ut_t);
  TTS_EXPR_IS(eve::bitwise_cast<float>(float()), float);
}
