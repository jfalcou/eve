//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ALL_HPP
#define ALL_HPP

#include <eve/function/scalar/all.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/tags.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check all return type") { TTS_EXPR_IS(eve::all(Type()), bool); }

TTS_CASE("Check eve::all behavior")
{
  TTS_EQUAL(eve::all(Type{0}), false);
  TTS_EQUAL(eve::all(Type{2}), true);
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::all(-0.0), false); //tested because of the high bit set
  }
}

#endif
