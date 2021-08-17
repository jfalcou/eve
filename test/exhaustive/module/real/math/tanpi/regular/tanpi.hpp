//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_odd.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on tanpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdtanpi =  tts::vectorize<T> ( [](auto x)
                                          {
                                            return  ((x < eve::maxflint(eve::as<v_t>())) && eve::is_odd(x*2))
                                                  ? eve::nan<v_t>()
                                                  : boost::math::sin_pi(x)/boost::math::cos_pi(x);
                                          }
                                        );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, my_stdtanpi, eve::tanpi);
}
