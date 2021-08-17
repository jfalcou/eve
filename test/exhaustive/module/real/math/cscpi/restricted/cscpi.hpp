//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cscpi", EVE_TYPE)
{
  auto my_stdcscpi =  tts::vectorize<T> ( [](auto x)
                                          {
                                            return  eve::rec(boost::math::sin_pi(x));
                                          }
                                        );

  eve::exhaustive_producer<T> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdcscpi, eve::restricted(eve::cscpi));
}
