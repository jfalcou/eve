//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cotpi", EVE_TYPE)
{
  auto my_stdcotpi =  tts::vectorize<T> ( [](auto x)
                                          {
                                            return boost::math::cos_pi(x)/boost::math::sin_pi(x);
                                          }
                                        );

  eve::exhaustive_producer<T> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdcotpi, eve::quarter_circle(eve::cotpi));
}
