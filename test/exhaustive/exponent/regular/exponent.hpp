//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exponent.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/inc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on exponent")
{
  // TODO exponent does not seem correct for denormals
  using i_t = eve::detail::as_integer_t<Value>; 
  auto internal_f = [](auto e){  int exp; std::frexp(e, &exp); return i_t(exp)-1; }; 
  using vi_t = eve::detail::as_integer_t<Type>; 
  auto std_exponent = tts::vectorize<vi_t>( [ internal_f ](auto e) { return internal_f(e); } );

  eve::exhaustive_producer<Type> p(eve::Smallestposval<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_exponent, eve::exponent); 
}
