//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/asecd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/rec.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide exhaustive check on asecd", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_asecd = tts::vectorize<T>( [](auto e) { return eve::radindeg(std::acos(eve::rec(e))); } );

  eve::exhaustive_producer<T> p1(eve::Valmin<v_t>(), v_t(-1));
  TTS_RANGE_CHECK(p1, std_asecd, eve::asecd);

  eve::exhaustive_producer<T> p2(v_t(1), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p2, std_asecd, eve::asecd);
}
