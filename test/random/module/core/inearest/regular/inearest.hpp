//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nearest.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on inearest")
{
  using EVE_VALUE   = eve::element_type_t<T>;
  using vi_t  = eve::detail::as_integer_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>;
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return i_t(std::nearbyint(e)); } );

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<i_t>()), eve::valmax(eve::as<i_t>()));
    TTS_RANGE_CHECK(p, std_inearest, eve::int_(eve::nearest));
  }
  else
  {
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return e; } );

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_inearest, eve::int_(eve::nearest));
  }
}
