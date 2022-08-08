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
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

TTS_CASE_TPL("Random check for eve::cscpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto my_stdcscpi  = [](auto x) -> e_t
                      {
                        return    (x == 0 || !eve::is_flint(x))
                                ? e_t(eve::rec(boost::math::sin_pi(double(x))))
                                : eve::nan(eve::as<e_t>());
                      };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  my_stdcscpi, eve::cscpi );
};
