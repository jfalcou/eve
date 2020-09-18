//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acoth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acoth", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acoth = tts::vectorize<T>( [](auto e) { return std::atanh(eve::rec(e)); } );

  eve::rng_producer<T> p1(v_t(1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p1, std_acoth, eve::acoth);

  eve::rng_producer<T> p2(eve::valmin(eve::as<v_t>()), v_t(-1));
  TTS_RANGE_CHECK(p2, std_acoth, eve::acoth);
}
