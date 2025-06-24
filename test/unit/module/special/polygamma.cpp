//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>
#include <eve/module/special/detail/cotderiv.hpp>
#include <cmath>

//==================================================================================================
// hurwitz  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of polygamma on wide", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using eve::polygamma;
  using e_t = eve::element_type_t<T>;

  auto ulp = 3.0;
  if constexpr(sizeof(e_t) == 8  && eve::cardinal_v<T> == 1)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(polygamma(3, eve::nan(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
      TTS_IEEE_EQUAL(T(polygamma(3, eve::nan(eve::as<e_t>()))), polygamma(3, eve::nan(eve::as<T>())));
      TTS_IEEE_EQUAL(polygamma(3, eve::inf(eve::as<e_t>())), eve::zero(eve::as<e_t>()));
      TTS_IEEE_EQUAL(T(polygamma(3, eve::inf(eve::as<e_t>()))), polygamma(3, eve::inf(eve::as<T>())));
      TTS_IEEE_EQUAL(polygamma(3, eve::minf(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
      TTS_IEEE_EQUAL(T(polygamma(3, eve::minf(eve::as<e_t>()))), polygamma(3, eve::minf(eve::as<T>())));
    }
    TTS_ULP_EQUAL(polygamma(3, e_t(0.125)), e_t(24580.14341906356621851100L), ulp);
    TTS_ULP_EQUAL(T(polygamma(3, e_t(0.125))), polygamma(3, T(0.125)), ulp);
    TTS_ULP_EQUAL(polygamma(3, e_t(6)), e_t(0.01182782819275507502194810L), ulp);
    TTS_ULP_EQUAL(T(polygamma(3, e_t(6))), polygamma(3, T(6)), ulp);
    TTS_ULP_EQUAL(polygamma(3, e_t(1)), e_t(6.49393940226682914909602217924700L), ulp);
    TTS_ULP_EQUAL(T(polygamma(3, e_t(1))), polygamma(3, T(1)), ulp);
    TTS_ULP_EQUAL(polygamma(3, e_t(15)),e_t(0.000654479778282737348417337L) , ulp);
    TTS_ULP_EQUAL(T(polygamma(3, e_t(15))), polygamma(3, T(15)), ulp);

    TTS_ULP_EQUAL(polygamma(3, e_t(-2.45)), e_t(214.66070346259589040673700L)    , ulp);
    TTS_ULP_EQUAL(T(polygamma(3, e_t(-2.45))), polygamma(3, T(-2.45)), ulp);

    {
      eve::wide<double, eve::fixed<4>> z{0.125, 15, 2.45, 1.0};
      eve::wide<double, eve::fixed<4>> r{24580.14341906357, 0.0006544797782827373,  0.24034527708135944, 6.493939402266837};
      TTS_ULP_EQUAL(polygamma(3, z), r    , ulp);
    }

    {
      eve::wide<double, eve::fixed<4>> z{eve::nan(eve::as(0.0)), 15, -2.25, eve::inf(eve::as(0.0))};
      eve::wide<double, eve::fixed<4>> r{eve::nan(eve::as(0.0)), 0.0006544797782827373, 1558.455023188714, 0.0};
      TTS_ULP_EQUAL(polygamma(3, z), r    , ulp);
    }

//     std::cout << "eve::polygamma(0, -2.25 ) "<< eve::polygamma(0, -2.25) << std::endl;
//     std::cout << "eve::digamma(-2.25)     ) "<< eve::digamma(-2.25)      << std::endl;
//     std::cout << "eve::polygamma(1, -2.25)  "<< eve::polygamma(1, -2.25) << std::endl;
//     std::cout << "eve::trigamma(-2.25)      "<< eve::trigamma(-2.25)      << std::endl;
//     std::cout << "eve::polygamma(2, -2.25)  "<< eve::polygamma(2, -2.25) << std::endl;
//     std::cout << "eve::polygamma(3, -2.25)  "<< eve::polygamma(3, -2.25) << std::endl;
//     std::cout << "eve::polygamma(4, -2.25)  "<< eve::polygamma(4, -2.25) << std::endl;
//     std::cout << "eve::polygamma(5, -2.25) "<< eve::polygamma(5, -2.25) << std::endl;



//     for(int i=100; i < 111 ; ++i)
//     {
//       std::cout << std::setprecision(16) << "eve::polygamma(" << i << ", -0.25) "<< eve::polygamma(i, -0.25) << std::endl;
//     }
//     for(int i=2; i < 4 ; ++i)
//     {
//       std::cout << "eve::polygamma(" << i << ", -2.25) "<< eve::polygamma(i, -2.25) << std::endl;
//     }
//     for(int i=0; i < 11 ; ++i)
//     {
//       std::cout << "eve::zeta(" << i << ", 0.75) "<< eve::hurwitz(i, 0.75) << std::endl;
//     }


 for(double x=-2; x >= -2.5; x+=-0.1)
 {
   std::cout << std::setprecision(16) << "eve::polygamma(3, x) "<< eve::polygamma(3, x) << std::endl;
 }
 for(double x=-2; x >= -2.5; x+=-0.1)
 {
   std::cout << std::setprecision(16) << "eve::hurwitz(3, 1-x) "<< eve::hurwitz(3, 1-x) << std::endl;
 }
//  for(double x=-2.1; x >= -2.5; x+=-0.1)
//  {
//    std::cout << std::setprecision(16) << "eve::detail::cotdern(3, x) "<< eve::detail::cotdern(3, x) << std::endl;
//  }

  }
};
