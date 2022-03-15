//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on secpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdsecpi =  tts::vectorize<T> ( [](auto x)
                                          {
                                            return  ((x < eve::maxflint(eve::as<v_t>())) && eve::is_odd(x*2))
                                                  ? eve::nan<v_t>()
                                                  : eve::rec(boost::math::cos_pi(x));
                                          }
                                        );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::secpi);
}
