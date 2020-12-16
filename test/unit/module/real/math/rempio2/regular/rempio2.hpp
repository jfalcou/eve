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
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>

TTS_CASE_TPL("Check eve::rempio2 behavior", EVE_TYPE)
{
  {
    auto [rn, rx, rdx]  = eve::rem_pio2(T(0));
    auto [ n,  x,  dx]  = eve::regular(eve::rempio2)(T(0));

    TTS_ULP_EQUAL(x, rx, 0.5 );
    TTS_ULP_EQUAL(n, rn, 0.5 );
  }

  {
    auto z = eve::detail::Rempio2_limit(eve::regular_type(), eve::as<T>())/2;
    auto [rn, rx, rdx]  = eve::rem_pio2(z);
    auto [ n,  x,  dx]  = eve::rempio2(z);

    TTS_ULP_EQUAL(x, rx, 0.5 );
    TTS_ULP_EQUAL(n, rn, 0.5 );
  }

  {
    auto z = eve::detail::Rempio2_limit(eve::regular_type(), eve::as<T>());
    auto [rn, rx, rdx]  = eve::rem_pio2(z);
    auto [ n,  x,  dx]  = eve::rempio2(z);

    TTS_ULP_EQUAL(x, rx, 0.5 );
    TTS_ULP_EQUAL(n, rn, 0.5 );
  }
}
