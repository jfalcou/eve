//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>
#include <string>

TTS_CASE_TPL( "Check dd::rec ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  using wdd_t  = eve::wide<dd_t>;
  if constexpr(sizeof(T) == 4)
  {
    auto pi = eve::pi(eve::as<double>());
    std::string spi = std::to_string(pi);
    std::cout << std::setprecision(20) << spi << std::endl;
    auto ddpi = dd_t(pi);
    auto ddpis= dd_t("+3.14159265358979323846264338327950e-00"); //28841971693993751");
//    auto ddpis= dd_t(spi.c_str());
    std::cout << ddpi << std::endl;
    TTS_ULP_EQUAL(pi,eve::to_double(ddpi), 4);
    TTS_ULP_EQUAL(pi,eve::to_double(ddpis), 108);
    std::cout << ddpis << std::endl;
  }
  auto dpi = eve::pi(eve::as<dd_t>());
  std:: cout<< "cts pi " << sizeof(T) << std::setprecision(sizeof(T)*5) << dpi << std::endl;
  auto wdpi = eve::pi(eve::as<wdd_t>());
  std:: cout<< "cts wdpi " << wdpi << std::endl;
};
