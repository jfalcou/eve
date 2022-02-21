//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/func/tmp/boost_math_cospi.hpp>
#include <eve/detail/func/tmp/boost_math_sinpi.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/trunc.hpp>
#include <eve/module/math/constant/invpi.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/function/is_odd.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on tanpi", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto my_stdtanpi  = [](auto x)
                      {
                        auto z = eve::abs(x);

                        if (z == eve::trunc(z))                 return   EVE_VALUE(0);
                        if (z-EVE_VALUE(0.5) == eve::trunc(z))  return eve::nan(eve::as<EVE_VALUE>());
                        if (eve::is_infinite(z)) return eve::nan(eve::as<EVE_VALUE>());
                        return  EVE_VALUE(boost::math::sin_pi(double(x))/boost::math::cos_pi(double(x)));
                      };

  TTS_RANGE_CHECK ( eve::uniform_prng<EVE_VALUE>( -2*eve::maxflint(eve::as<EVE_VALUE>())
                                                , 2*eve::maxflint(eve::as<EVE_VALUE>())
                                                )
                  , my_stdtanpi, eve::tanpi
                  );
};
