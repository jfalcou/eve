//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/touint.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::touint return type")
{
  TTS_EXPR_IS(eve::touint(EVE_TYPE(0)), (eve::detail::as_integer_t<EVE_TYPE, unsigned>));
}

TTS_CASE("Check eve::touint behavior")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

  TTS_EQUAL(eve::touint(EVE_TYPE( 1.2357)), static_cast<r_t>( 1.2357));
  TTS_EQUAL(eve::touint(EVE_TYPE( 1))     , static_cast<r_t>( 1));
  TTS_EQUAL(eve::touint(EVE_TYPE( 0))     , static_cast<r_t>( 0));

  if constexpr( std::is_floating_point_v<EVE_VALUE> )
  {
    TTS_EQUAL(eve::touint(eve::Mzero<EVE_TYPE>()), r_t(0));
  }
}
