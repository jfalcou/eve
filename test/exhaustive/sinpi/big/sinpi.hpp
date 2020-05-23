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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on sinpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto my_stdsinpi =  tts::vectorize<T>([](auto x){return boost::math::sin_pi(x); });

  eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::big_(eve::sinpi));
}

// #include <crlibm.h>

// TTS_CASE_TPL("wide exhaustive check on sinpi", EVE_TYPE)
// {
//   ::crlibm_init();
//   using v_t = eve::element_type_t<T>;
//   auto my_stdsinpi =  tts::vectorize<T>([](v_t x){return v_t(::sinpi_rn(x)); });
//   eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
//   TTS_RANGE_CHECK(p, my_stdsinpi, eve::big_(eve::sinpi));
// }
