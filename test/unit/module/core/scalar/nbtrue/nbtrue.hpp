//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NBTRUE_HPP
#define NBTRUE_HPP

#include <eve/function/scalar/nbtrue.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/tags.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check nbtrue return type") { TTS_EXPR_IS(eve::nbtrue(Type()), size_t); }

TTS_CASE("Check eve::nbtrue behavior")
{
  TTS_EQUAL(eve::nbtrue(Type{0}), 0u);
  TTS_EQUAL(eve::nbtrue(Type{2}), 1u);
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::nbtrue(-0.0), 0u); //tested because of the high bit set
  }
}

#endif
