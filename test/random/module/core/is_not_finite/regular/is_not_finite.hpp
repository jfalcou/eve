//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_finite.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on is_not_finite")
{
  using l_t =  eve::as_logical_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_is_not_finite = tts::vectorize<l_t>( [](auto e)
                                                  {
                                                    return  (std::fpclassify(e) == FP_INFINITE)
                                                        ||  (std::fpclassify(e) == FP_NAN);
                                                  }
                                                );

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_not_finite, eve::is_not_finite);
  }
  else
  {
    auto std_is_not_finite = tts::vectorize<l_t>( [](auto ) { return false; } );
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_not_finite, eve::is_not_finite);
  }
}
