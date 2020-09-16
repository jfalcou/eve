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
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on next", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_next = tts::vectorize<T> ( [](auto e)
                                        { return    (e == 0) && eve::is_negative(e) ? v_t(0)
                                                  : ( ( e ==  eve::inf(eve::as<v_t>())) ? eve::nan<v_t>()
                                                          : std::nextafter(e, eve::inf(eve::as<v_t>())
                                                      )
                                                    );
                                        }
                                      );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_ULP_RANGE_CHECK(p, std_next, eve::pedantic_(eve::next), 0);
  }
  else
  {
    auto std_next = tts::vectorize<T>( [](auto e) { return e == eve::valmax(eve::as<v_t>()) ? e : e+1; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_ULP_RANGE_CHECK(p, std_next, eve::pedantic_(eve::next), 0);
  }
}
