//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::secpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto my_stdsecpi  = [](auto x)
                      {
                        auto z = eve::abs(x);

                        if (z >= eve::maxflint(eve::as(x))) return e_t(1);
                        if (eve::is_even(z)) return   e_t(1);
                        if (eve::is_infinite(z)) return eve::nan(eve::as<e_t>());
                        if ((z-e_t(0.5) == eve::trunc(z)) && (z != z-e_t(0.5) ))
                          return eve::nan(eve::as<e_t>());

                        return  e_t(eve::rec(boost::math::cos_pi(double(x))));
                      };

  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  my_stdsecpi, eve::secpi );
};
