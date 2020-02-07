//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/popcount.hpp>
#include <eve/logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on is_pow2")
{
  using l_t = eve::as_logical_t<Type>; 
  auto std_is_pow2 = tts::vectorize<l_t>( [](auto e)
    { return ((e > 0) && (eve::popcount(e) == 1u)); }
  );
  eve::rng_producer<Type> p(eve::Zero<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_is_pow2, eve::is_pow2);
}
