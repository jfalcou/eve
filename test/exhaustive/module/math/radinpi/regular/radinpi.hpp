//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/radinpi.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on inpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_inpi = tts::vectorize<T>( [](auto e) { return eve::Invpi<v_t>()*e; } );

  eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_inpi, eve::radinpi);
}
