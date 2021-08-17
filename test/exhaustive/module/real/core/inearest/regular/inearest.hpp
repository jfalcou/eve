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
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on inearest", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  using vi_t  = eve::as_integer_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using i_t =  eve::as_integer_t<v_t>;
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return i_t(std::nearbyint(e)); } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<i_t>()), eve::valmax(eve::as<i_t>()));
    TTS_RANGE_CHECK(p, std_inearest,  eve::int_(eve::nearest));
  }
  else
  {
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return e; } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_inearest,  eve::int_(eve::nearest));
  }
}
