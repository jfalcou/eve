//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rempio2.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>

TTS_CASE("Check eve::small(eve::rempio2) behavior")
{
  {
    auto [rn, rx, rdx]  = eve::rem_pio2(EVE_TYPE(0));
    auto [ n,  x,  dx]  = eve::small(eve::rempio2)(EVE_TYPE(0));

    TTS_ULP_EQUAL(x, rx, 0.5 );
    TTS_ULP_EQUAL(n, rn, 0.5 );
  }

  {
    auto z = eve::detail::Rempio2_limit(eve::small_type(), eve::as<EVE_TYPE>())/2;
    auto [rn, rx, rdx]  = eve::rem_pio2(z);
    auto [ n,  x,  dx]  = eve::small(eve::rempio2)(z);

    TTS_ULP_EQUAL(x, rx, 0.5 );
    TTS_ULP_EQUAL(n, rn, 0.5 );
  }

  {
    auto z = eve::detail::Rempio2_limit(eve::small_type(), eve::as<EVE_TYPE>());
    auto [rn, rx, rdx]  = eve::rem_pio2(z);
    auto [ n,  x,  dx]  = eve::small(eve::rempio2)(z);

    TTS_ULP_EQUAL(x, rx, 0.5 );
    TTS_ULP_EQUAL(n, rn, 0.5 );
  }
}
