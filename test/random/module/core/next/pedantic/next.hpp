//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/next.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide rng check on next")
{

  if constexpr(eve::floating_value<T>)
  {
    auto std_next = tts::vectorize<T> ( [](auto e)
                                        { return    (e == 0) && eve::is_negative(e) ? EVE_VALUE(0)
                                                  : ( ( e ==  eve::inf(eve::as<EVE_VALUE>())) ? eve::nan(eve::as<EVE_VALUE>())
                                                          : std::nextafter(e, eve::inf(eve::as<EVE_VALUE>())
                                                      )
                                                    );
                                        }
                                      );

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_next, eve::pedantic(eve::next), 0);
  }
  else
  {
    auto std_next = [](auto e) { return e == eve::valmax(eve::as<EVE_VALUE>()) ? e : e+1; } );
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_next, eve::pedantic(eve::next), 0);
  }
}
