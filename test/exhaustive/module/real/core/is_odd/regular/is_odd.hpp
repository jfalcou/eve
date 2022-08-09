//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/traits/as_logical.hpp>
#include <eve/module/core.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_odd", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using l_t = eve::as_logical_t<T>;
    auto std_is_odd = tts::vectorize<l_t> ( [](auto e)
                                            { auto da = eve::dec(e);
                                              return (e!= da) && eve::is_even(da);
                                            }
                                          );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
  else
  {
    using l_t = eve::as_logical_t<T>;
    auto std_is_odd = tts::vectorize<l_t>( [](auto e) { return  (e/2)*2!= e; } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
}
