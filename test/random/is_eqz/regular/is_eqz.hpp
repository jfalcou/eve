//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_eqz.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/as_logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on is_eqz")
{
  using l_t = eve::as_logical_t<Type>; 
  auto std_is_eqz = tts::vectorize<l_t>( [](auto e) { return e == Value(0); } );
  eve::rng_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_is_eqz, eve::is_eqz);
}
