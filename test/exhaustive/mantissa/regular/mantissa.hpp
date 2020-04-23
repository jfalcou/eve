//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mantissa.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on mantissa", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  // TODO problem with denormals
  auto internal_f = [](auto e){  int exp; return std::frexp(e, &exp)*2;  };
  auto std_mantissa = tts::vectorize<T>( [ internal_f ](auto e) { return internal_f(e); } );

  eve::exhaustive_producer<T> p(eve::Smallestposval<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_mantissa, eve::mantissa);
}
