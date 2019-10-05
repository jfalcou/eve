//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include <eve/function/extract.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check extract return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  TTS_EXPR_IS(eve::extract(Type(), i_t()), Type);
  TTS_EXPR_IS(eve::extract(Type(), u_t()), Type);
  TTS_EXPR_IS(eve::extract(Type(), int()), Type);
}

TTS_CASE("Check eve::extract behavior")
{
  TTS_EQUAL(eve::extract(Type{0}, 0), Type{0});
}

#endif
