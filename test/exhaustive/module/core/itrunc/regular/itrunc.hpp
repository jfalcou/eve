//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/itrunc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on itrunc", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using vi_t =  eve::detail::as_integer_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using i_t =  eve::detail::as_integer_t<v_t>;
    auto std_itrunc = tts::vectorize<vi_t>( [](auto e) { return i_t(std::trunc(e)); } );
    eve::exhaustive_producer<T> p(eve::Valmin<i_t>(), eve::Valmax<i_t>());
    TTS_RANGE_CHECK(p, std_itrunc, eve::itrunc);
  }
  else
  {
    auto std_itrunc = tts::vectorize<vi_t>( [](auto e) { return e; } );
    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_itrunc, eve::itrunc);
  }
}
