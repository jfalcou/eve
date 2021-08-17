//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cotpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdcotpi =  tts::vectorize<T> ( [](auto x)
                                          { return   (x == 0 || !eve::is_flint(x))
                                                    ? boost::math::cos_pi(x)/boost::math::sin_pi(x)
                                                    : eve::nan<v_t>();
                                          }
                                        );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, my_stdcotpi, eve::big(eve::cotpi));
}
