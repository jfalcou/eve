//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/nearest.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on inearest", EVE_TYPE)
<typename T>(::tts::type<T>)
{

  using i_t  = eve::as_integer_t<EVE_VALUE>;

  if constexpr(eve::floating_value<T>)
  {
    using i_t =  eve::as_integer_t<EVE_VALUE>;
    auto std_inearest =  [](auto e)  ->i_t { return i_t(std::nearbyint(e)); };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<i_t>()), eve::valmax(eve::as<i_t>()));
    TTS_RANGE_CHECK(p, std_inearest, eve::int_(eve::nearest));
  }
  else
  {
    auto std_inearest = [](auto e) -> i_t { return e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_inearest, eve::int_(eve::nearest));
  }
};