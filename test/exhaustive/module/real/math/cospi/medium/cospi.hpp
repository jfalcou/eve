//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/cospi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide random check on cospi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto my_stdcospi =  tts::vectorize<T>([](auto x){return boost::math::cos_pi(x); });

  eve::exhaustive_producer<T> p(v_t(-100000.0), v_t(100000.0));
  TTS_RANGE_CHECK(p, my_stdcospi, eve::medium(eve::cospi));
}
