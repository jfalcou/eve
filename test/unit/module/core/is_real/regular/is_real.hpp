//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_REAL_HPP
#define IS_REAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_real.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_real return type")
{
  TTS_EXPR_IS(eve::is_real(EVE_TYPE(0)), eve::as_logical_t<EVE_TYPE>);
}

TTS_CASE("Check eve::is_real behavior")
{
  TTS_EQUAL(eve::is_real(EVE_TYPE{0}), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::is_real(EVE_TYPE{2}), eve::True<EVE_TYPE>());
}

#endif
