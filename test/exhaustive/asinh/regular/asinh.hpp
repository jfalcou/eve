//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on asinh", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_asinh = tts::vectorize<T>( [](auto e) { return std::asinh(e); } );

  eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_asinh, eve::asinh);
}
