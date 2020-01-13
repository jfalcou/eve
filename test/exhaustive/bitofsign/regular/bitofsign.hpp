//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/shl.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/one.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on bitofsign")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_bitofsign = tts::vectorize<Type>( [](auto e) { return std::copysign(eve::One<Value>(), e); } );
    auto eve_bitofsign = [](auto e) { return eve::bitwise_xor(eve::bitofsign(e), eve::One<Value>()); }; 
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_bitofsign, eve_bitofsign);
  }
  else 
  {
    auto std_bitofsign = tts::vectorize<Type>( [](auto e) {
                                                 using i_t = eve::detail::as_integer_t<Value>; 
                                                 return  Value(i_t(std::signbit(e)) << (sizeof(e)*8-1)); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_bitofsign, eve::bitofsign);
  }
  
}
