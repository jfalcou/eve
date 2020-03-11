//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/toint.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::toint return type")
{
  TTS_EXPR_IS(eve::toint(EVE_TYPE(0)), (eve::detail::as_integer_t<EVE_TYPE>));
}

TTS_CASE("Check eve::toint behavior")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE>;

  TTS_EQUAL(eve::toint(EVE_TYPE(1.2357)), static_cast<r_t>(1.2357));
  TTS_EQUAL(eve::toint(EVE_TYPE(1))     , r_t(1));
  TTS_EQUAL(eve::toint(EVE_TYPE(0))     , r_t(0));

  if constexpr( std::is_floating_point_v<EVE_VALUE> )
  {
    TTS_EQUAL(eve::toint(eve::Mzero<EVE_TYPE>()), r_t(0));
  }
}
