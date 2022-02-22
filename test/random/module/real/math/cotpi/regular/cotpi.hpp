//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/module/math/constant/invpi.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cotpi", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto my_stdcotpi  = [](auto x)
                      { return    (x == 0 || !eve::is_flint(x))
                                ? boost::math::cos_pi(x)/boost::math::sin_pi(x)
                                : eve::nan(eve::as<EVE_VALUE>());
                      };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK_WITH(p, my_stdcotpi, eve::cotpi, 4);
};
