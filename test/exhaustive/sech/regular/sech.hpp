//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sech.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on sech", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sech = tts::vectorize<T>( [](auto e) { return v_t(1)/std::cosh(double(e)); } );

  eve::exhaustive_producer<T> p(eve::Minlog<v_t>()+1, eve::Maxlog<v_t>()-1);
  TTS_RANGE_CHECK(p, std_sech, eve::sech);
}
