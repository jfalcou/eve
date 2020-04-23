//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/sinpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide exhaustive check on sinpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto my_stdsinpi =  tts::vectorize<T>([](auto x){return boost::math::sin_pi(x); });
  eve::exhaustive_producer<T> p(v_t(-100000.0), v_t(100000.0));
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::medium_(eve::sinpi));
}
