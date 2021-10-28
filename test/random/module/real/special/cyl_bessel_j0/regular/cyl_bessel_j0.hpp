//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cyl_bessel_j0", EVE_TYPE)
{
  auto bj0 = [](auto x) -> EVE_VALUE {return boost::math::cyl_bessel_j(EVE_VALUE(0), x); };

  eve::uniform_prng<EVE_VALUE> p(0, 4);
  TTS_RANGE_CHECK(p, bj0, eve::cyl_bessel_j0);
}
