//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>
#include <eve/function/cyl_bessel_jn.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cyl_bessel_jn", EVE_TYPE)
{
  EVE_VALUE n;
  eve::uniform_prng<EVE_VALUE> p(0, 12);

  for(EVE_VALUE n=0; n < EVE_VALUE(5) ; n+= 0.25)
  {
    auto bjn = [n](auto x) -> EVE_VALUE {return boost::math::cyl_bessel_j(n, x); };
    auto  jn = [n](auto x) -> EVE_VALUE {return eve::cyl_bessel_jn(n, x); };
    TTS_RANGE_CHECK(p, bjn, jn);
  }
}
