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
#include <eve/function/erfcx.hpp>
#include <eve/function/prev.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on gamma", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_erfcx = tts::vectorize<T>([](auto e) { return eve::erfcx(double(e)); });

  eve::exhaustive_producer<T> p(v_t(-7), v_t(-1)); //eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_erfcx, eve::erfcx);
}
