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
#include <eve/function/cscpi.hpp>
#include <tts/tests/range.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide random check on cscpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdcscpi =  tts::vectorize<T> ( [](auto x)
                                          {
                                            return    (x == 0 || !eve::is_flint(x))
                                                    ? eve::rec(boost::math::sin_pi(x))
                                                    : eve::nan(eve::as<v_t>());
                                          }
                                        );

  eve::rng_producer<T> p(v_t(-100000.0), v_t(100000.0));
  TTS_RANGE_CHECK(p, my_stdcscpi, eve::medium_(eve::cscpi));
}
