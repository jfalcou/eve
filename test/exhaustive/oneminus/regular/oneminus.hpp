//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on oneminus")
{
  if constexpr(std::is_signed_v<Value>)
  {
    auto std_oneminus = tts::vectorize<Type>( [](auto e) { return  Value(1)-e; });
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);
  }
  else
  {
    auto std_oneminus = tts::vectorize<Type>( [](auto e) { return  static_cast<Value>(eve::One<Value>()-e);} );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_oneminus,  eve::oneminus);
  }  
}
