//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on oneminus", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(std::is_unsigned_v<v_t>)
  {
    auto std_oneminus = tts::vectorize<T>( [](auto e) { return v_t(1)-e; } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);
  }
  else
  {
    auto std_oneminus = tts::vectorize<T>( [](auto e) { return v_t(1)-e; } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);
  }
}
