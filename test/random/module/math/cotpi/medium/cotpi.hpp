//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <tts/tests/range.hpp>
#include <cmath>

TTS_CASE_TPL("wide random check on cotpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdcotpi =  tts::vectorize<T> ( [](auto x)
                                          { return    (x == 0 || !eve::is_flint(x))
                                                    ? boost::math::cos_pi(x)/boost::math::sin_pi(x)
                                                    : eve::nan<v_t>();
                                          }
                                        );

  eve::rng_producer<T> p(v_t(-100000.0), v_t(100000.0));
  TTS_RANGE_CHECK(p, my_stdcotpi, eve::medium_(eve::cotpi));
}
