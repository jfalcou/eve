//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

using Type = double;
#include "bitwise_cast.hpp"
TTS_CASE("Check bitwise_cast return type")
{
  using ut_t = eve::detail::as_integer_t<double, unsigned>;
  using it_t = eve::detail::as_integer_t<double, signed>;
  TTS_EXPR_IS(eve::bitwise_cast<it_t>(double()), it_t);
  TTS_EXPR_IS(eve::bitwise_cast<ut_t>(double()), ut_t);
  TTS_EXPR_IS(eve::bitwise_cast<double>(double()), double);
}
