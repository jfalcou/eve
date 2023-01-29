//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>


TTS_CASE_TPL( "Check dd::rec ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  // using wdd_t  = eve::wide<dd_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    auto ddpi = dd_t(pi);
    std::cout << ddpi << std::endl;
    auto rpi = eve::rec(ddpi);
    TTS_ULP_EQUAL(eve::rec(pi), eve::to_double(rpi), 10);
  }
};
