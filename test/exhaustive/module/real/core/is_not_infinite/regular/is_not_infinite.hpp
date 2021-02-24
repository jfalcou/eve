//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_infinite.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_not_infinite", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t =  eve::as_logical_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_is_not_infiniteinite = tts::vectorize<l_t>( [](auto e) { return !std::isinf(e); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_is_not_infiniteinite, eve::is_not_infinite);
  }
  else
  {
    auto std_is_not_infiniteinite = tts::vectorize<l_t>( [](auto ) { return true; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_is_not_infiniteinite, eve::is_not_infinite);
  }
}
