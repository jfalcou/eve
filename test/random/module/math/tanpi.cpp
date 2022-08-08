//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

TTS_CASE_TPL("Random check for eve::tanpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto my_stdtanpi  = [](auto x)
                      {
                        auto z = eve::abs(x);

                        if (z == eve::trunc(z))                 return   e_t(0);
                        if (z-e_t(0.5) == eve::trunc(z))  return eve::nan(eve::as<e_t>());
                        if (eve::is_infinite(z)) return eve::nan(eve::as<e_t>());
                        return  e_t(boost::math::sin_pi(double(x))/boost::math::cos_pi(double(x)));
                      };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  my_stdtanpi, eve::tanpi );
};
