//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on find", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_find = tts::vectorize<T>( [](auto e) { return std::find(e); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_find, eve::find);
  }
  else if constexpr(eve::signed_value<T>)
  {
    auto std_find = tts::vectorize<T>( [](auto e) { return  std::find(e); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_find, eve::find);
  }
  else
  {
    auto std_find = tts::vectorize<T>( [](auto e) { return e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_find, eve::find);
  }
}
