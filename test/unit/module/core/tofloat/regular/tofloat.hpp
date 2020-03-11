//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tofloat.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::tofloat return type")
{
  TTS_EXPR_IS( (eve::tofloat(EVE_TYPE())), (eve::detail::as_floating_point_t<EVE_TYPE>));
}

TTS_CASE("Check eve::tofloat behavior")
{
  using r_t = eve::detail::as_floating_point_t<EVE_TYPE>;

  if constexpr( std::is_signed_v<EVE_VALUE> )
  {
    TTS_EQUAL(eve::tofloat(EVE_TYPE(-2)), r_t(-2));
  }

  TTS_EQUAL(eve::tofloat(EVE_TYPE( 0)), r_t( 0));
  TTS_EQUAL(eve::tofloat(EVE_TYPE( 2)), r_t( 2));
}
