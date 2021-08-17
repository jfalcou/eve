//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/prev.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on prev", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_prev = tts::vectorize<T>( [](auto e) { return (e == 0) && eve::is_positive(e) ? v_t(-0.)
                                                  : (e ==  eve::minf(eve::as<v_t>())) ?  eve::nan<v_t>() : std::nextafter(e, eve::minf(eve::as<v_t>())); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::pedantic(eve::prev));
  }
  else
  {
    auto std_prev = tts::vectorize<T>( [](auto e) { return e == eve::valmin(eve::as<v_t>()) ? e : e-1; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::pedantic(eve::prev));
  }
}
