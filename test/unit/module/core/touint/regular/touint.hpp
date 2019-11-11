//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::touint(Type(0)), (eve::detail::as_integer_t<Type, unsigned>));
}

TTS_CASE("Check eve::touint behavior")
{
  using r_t = eve::detail::as_integer_t<Type, unsigned>;

  TTS_EQUAL(eve::touint(Type( 1.2357)), static_cast<r_t>( 1.2357));
  TTS_EQUAL(eve::touint(Type( 1))     , static_cast<r_t>( 1));
  TTS_EQUAL(eve::touint(Type( 0))     , static_cast<r_t>( 0));

  if constexpr( std::is_floating_point_v<Value> )
  {
    TTS_EQUAL(eve::touint(eve::Mzero<Type>()), r_t(0));
  }
}
