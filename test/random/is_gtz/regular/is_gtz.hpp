//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_gtz.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on is_gtz")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_is_gtz = tts::vectorize<Type>( [](auto e) { return std::is_gtz(e); } );
    eve::rng_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_gtz, eve::is_gtz);
  }
  else if constexpr(std::is_signed_v<Value>)
  {
    auto std_is_gtz = tts::vectorize<Type>( [](auto e) { return  std::is_gtz(e); } );
    eve::rng_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_gtz, eve::is_gtz);
  }
  else
  {
    auto std_is_gtz = tts::vectorize<Type>( [](auto e) { return e; } );
    eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_gtz, eve::is_gtz);
  }
  
  
}
