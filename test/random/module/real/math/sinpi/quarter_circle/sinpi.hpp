//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/sinpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sinpi", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto my_stdsinpi = [](auto x){return boost::math::sin_pi(x); };

  eve::uniform_prng<EVE_VALUE> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::quarter_circle(eve::sinpi));
};