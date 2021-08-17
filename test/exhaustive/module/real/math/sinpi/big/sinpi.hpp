//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on sinpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdsinpi =  tts::vectorize<T>([](auto x){return boost::math::sin_pi(x); });
  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::big(eve::sinpi));
}

// #include <crlibm.h>

// TTS_CASE_TPL("wide random check on sinpi", EVE_TYPE)
// {
//   ::crlibm_init();
//   auto my_stdsinpi =  tts::vectorize<T>([](v_t x){return v_t(::sinpi_rn(x)); });
//   eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
//   TTS_RANGE_CHECK(p, my_stdsinpi, eve::big(eve::sinpi));
// }
