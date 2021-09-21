//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/popcount.hpp>
#include <eve/logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_pow2", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t = eve::as_logical_t<T>;
  auto std_is_pow2 = tts::vectorize<l_t>( [](auto e)
                                          {
                                            return ((e > 0) && (eve::popcount(e) == 1u));
                                          }
                                        );

  eve::exhaustive_producer<T> p(eve::zero(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_is_pow2, eve::is_pow2);
}
