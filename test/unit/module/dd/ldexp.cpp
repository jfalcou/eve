//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/dd.hpp>


TTS_CASE_TPL( "Check dd::ldexp ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  // using wdd_t  = eve::wide<dd_t>;
  double pi = eve::pi(eve::as<double>());
  auto ddpi = dd_t(pi);
  std::cout << std::setprecision(2*sizeof(T)) << ddpi << std::endl;
  auto rpi = eve::ldexp(ddpi, 3);
  std::cout << rpi << std::endl;
  if constexpr(sizeof(T) == 4)
  {
    TTS_ULP_EQUAL(eve::ldexp(pi, 3), eve::ldexp(eve::to_double(ddpi), 3), 4);
  }
  std::cout << std::setprecision(2*sizeof(T)) << eve::inc( eve::eps(eve::as(ddpi))/2) << std::endl;
  std::cout << std::setprecision(2*sizeof(T)) << eve::next(eve::one(eve::as(ddpi))  ) << std::endl;
  std::cout << std::setprecision(2*sizeof(T)) << dd_t(eve::one(eve::as<T>()), eve::smallestposval(eve::as<T>())) << std::endl;
};
