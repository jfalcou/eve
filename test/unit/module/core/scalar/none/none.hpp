//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NONE_HPP
#define NONE_HPP

#include <eve/function/scalar/none.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/tags.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check none return type") { TTS_EXPR_IS(eve::none(Type()), bool); }

TTS_CASE("Check eve::none behavior")
{
  TTS_EQUAL(eve::none(Type{0}), true);
  TTS_EQUAL(eve::none(Type{2}), false);
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::none(-0.0), true); //tested because of the high bit set
  }
}

#endif
