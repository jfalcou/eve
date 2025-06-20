//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// hurwitz  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of polygamma on wide", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using eve::polygamma;
  using e_t = eve::element_type_t<T>;

//  auto ulp = 2.0;
  if constexpr(sizeof(e_t) == 8  && eve::cardinal_v<T> == 1)
  {
//     if constexpr( eve::platform::supports_invalids )
//     {
//       TTS_IEEE_EQUAL(polygamma(3, eve::nan(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
//       TTS_IEEE_EQUAL(T(polygamma(3, eve::nan(eve::as<e_t>()))), polygamma(3, eve::nan(eve::as<T>())));
//       TTS_IEEE_EQUAL(polygamma(3, eve::inf(eve::as<e_t>())), eve::zero(eve::as<e_t>()));
//       TTS_IEEE_EQUAL(T(polygamma(3, eve::inf(eve::as<e_t>()))), polygamma(3, eve::inf(eve::as<T>())));
//       TTS_IEEE_EQUAL(polygamma(3, eve::minf(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
//       TTS_IEEE_EQUAL(T(polygamma(3, eve::minf(eve::as<e_t>()))), polygamma(3, eve::minf(eve::as<T>())));
//     }
//     TTS_ULP_EQUAL(polygamma(3, e_t(0.125)), e_t(24580.14341906356621851100L), ulp);
//     TTS_ULP_EQUAL(T(polygamma(3, e_t(0.125))), polygamma(3, T(0.125)), ulp);
//     TTS_ULP_EQUAL(polygamma(3, e_t(6)), e_t(0.01182782819275507502194810L), ulp);
//     TTS_ULP_EQUAL(T(polygamma(3, e_t(6))), polygamma(3, T(6)), ulp);
//     TTS_ULP_EQUAL(polygamma(3, e_t(1)), e_t(6.49393940226682914909602217924700L), ulp);
//     TTS_ULP_EQUAL(T(polygamma(3, e_t(1))), polygamma(3, T(1)), ulp);
//     TTS_ULP_EQUAL(polygamma(3, e_t(15)),e_t(0.000654479778282737348417337L) , ulp);
//     TTS_ULP_EQUAL(T(polygamma(3, e_t(15))), polygamma(3, T(15)), ulp);

//    TTS_ULP_EQUAL(polygamma(2, e_t(-2.45)), e_t(214.66070346259589040673700L)    , ulp);
//    TTS_ULP_EQUAL(T(polygamma(3, e_t(-2.45))), polygamma(3, T(-2.45)), ulp);

//     {
//       eve::wide<double, eve::fixed<4>> z{0.125, 15, -2.45, 1.0};
//       eve::wide<double, eve::fixed<4>> r{512.8766690590678412978, 0.0023753013582757773733, 17.761703009137815, 1.2020569031595942853997};
//       TTS_ULP_EQUAL(polygamma(3, z), r    , ulp);
//     }

//     {
//       eve::wide<double, eve::fixed<4>> z{eve::nan(eve::as(0.0)), 15, -2.45, eve::inf(eve::as(0.0))};
//       eve::wide<double, eve::fixed<4>> r{eve::nan(eve::as(0.0)), 0.0023753013582757773733, 17.761703009137815, 0.0};
//       TTS_ULP_EQUAL(polygamma(3, z), r    , ulp);
//     }

    std::cout << "eve::polygamma(0, -2.25 ) "<< eve::polygamma(0, -2.25) << std::endl;
    std::cout << "eve::digamma(-2.25)     ) "<< eve::digamma(-2.25)      << std::endl;
    std::cout << "eve::polygamma(1, -2.25)  "<< eve::polygamma(1, -2.25) << std::endl;
    std::cout << "eve::trigamma(-2.25)      "<< eve::trigamma(-2.25)      << std::endl;
    std::cout << "eve::polygamma(2, -2.25)  "<< eve::polygamma(2, -2.25) << std::endl;
    std::cout << "eve::polygamma(3, -2.25)  "<< eve::polygamma(3, -2.25) << std::endl;
    std::cout << "eve::polygamma(4, -2.25)  "<< eve::polygamma(4, -2.25) << std::endl;
    std::cout << "eve::polygamma(5, -2.25) "<< eve::polygamma(5, -2.25) << std::endl;
 }

};
