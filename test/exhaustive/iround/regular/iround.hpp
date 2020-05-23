//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/iround.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on iround", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using vi_t =  eve::detail::as_integer_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using i_t =  eve::detail::as_integer_t<v_t>;
    auto std_iround = tts::vectorize<vi_t>( [](auto e) { return i_t(std::nearbyint(e)); } );
    eve::exhaustive_producer<T> p(eve::Valmin<i_t>(), eve::Valmax<i_t>());
    TTS_RANGE_CHECK(p, std_iround, eve::iround);
  }
  else
  {
    auto std_iround = tts::vectorize<vi_t>( [](auto e) { return e; } );
    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_iround, eve::iround);
  }
}
