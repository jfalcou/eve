//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on ifrexp", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  auto std_ifrexp = tts::vectorize<T>( [](auto e) { int y; auto x = std::frexp(e, &y); return std::make_tuple(x, i_t(y)); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_ifrexp, eve::raw(eve::ifrexp));
}
