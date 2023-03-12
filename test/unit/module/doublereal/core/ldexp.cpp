//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
//TODO

TTS_CASE_TPL( "Check doublereal::ldexp ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using doublereal_t   = eve::doublereal<T>;
  // using w_t    = eve::wide<T>;
  // using wdoublereal_t  = eve::wide<doublereal_t>;
  double pi = eve::pi(eve::as<double>());
  auto doublerealpi = doublereal_t(pi);
  std::cout << std::setprecision(2*sizeof(T)) << doublerealpi << std::endl;
  auto rpi = eve::ldexp(doublerealpi, 3);
  std::cout << rpi << std::endl;
  if constexpr(sizeof(T) == 4)
  {
    TTS_ULP_EQUAL(eve::ldexp(pi, 3), eve::ldexp(eve::to_double(doublerealpi), 3), 4);
  }
  std::cout << std::setprecision(2*sizeof(T)) << eve::inc( eve::eps(eve::as(doublerealpi))/2) << std::endl;
  std::cout << std::setprecision(2*sizeof(T)) << eve::next(eve::one(eve::as(doublerealpi))  ) << std::endl;
  std::cout << std::setprecision(2*sizeof(T)) << doublereal_t(eve::one(eve::as<T>()), eve::smallestposval(eve::as<T>())) << std::endl;
};
