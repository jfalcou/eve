//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on iceil", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using vi_t =  eve::as_integer_t<T>;
    using i_t = eve::element_type_t<vi_t>;
    auto std_iceil = tts::vectorize<vi_t>( [](auto e) { return i_t(std::ceil(e)); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<i_t>()), eve::valmax(eve::as<i_t>()));
    TTS_RANGE_CHECK(p, std_iceil, eve::int_(eve::ceil));
  }
  else
  {
    auto std_iceil = tts::vectorize<T>( [](auto e) { return e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_iceil, eve::int_(eve::ceil));
  }
}
