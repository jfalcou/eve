//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cyl_bessel_j1", EVE_TYPE)
{
  auto bj1 = [](auto x) -> EVE_VALUE {return boost::math::cyl_bessel_j(EVE_VALUE(1), x); };

  eve::uniform_prng<EVE_VALUE> p(0, 4);
  TTS_RANGE_CHECK(p, bj1, eve::cyl_bessel_j1);
}
