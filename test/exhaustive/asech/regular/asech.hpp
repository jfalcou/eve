//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asech.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on asech", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_asech = tts::vectorize<T>( [](auto e) { return std::acosh(eve::rec(e)); } );

  eve::exhaustive_producer<T> p(v_t(-1), v_t(1));
  TTS_RANGE_CHECK(p, std_asech, eve::asech);
}
