//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gcd.hpp>
#include <eve/platform.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/value.hpp>

TTS_CASE_TPL("Check eve::anp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::gcd(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::gcd behavior", EVE_TYPE)
{

//  auto eve__gcd =  [](auto n, auto p) { return eve::gcd(n, p); };

 //  if constexpr( eve::floating_value<T> )
//   {
//     TTS_ULP_EQUAL(eve__gcd(T(2), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
//     TTS_ULP_EQUAL(eve__gcd(T(2), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
//     TTS_ULP_EQUAL(eve__gcd(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
//   }

//   TTS_ULP_EQUAL(eve__gcd(T(10), T(5)), T(5), 0);
//   TTS_ULP_EQUAL(eve__gcd(T(6), T(2)), T(2), 0);
//   TTS_ULP_EQUAL(eve__gcd(T(36), T(45)), T(9), 0);
//   TTS_ULP_EQUAL(eve__gcd(T(1), T(0)), T(1), 0);
//   TTS_ULP_EQUAL(eve__gcd(T(0), T(0)), T(0), 0);
//   TTS_ULP_EQUAL(eve__gcd(T(0), T(1)), T(1), 0);

  using w_t = eve::wide < std::int8_t>; //, eve::fixed < 32 > >;
//   {
//     w_t a (14, 21, 8, 22, 31, 8, 19, 36, 26, 1, 12, 24, 11, 8, 30, 1, 4, 20, 21, 50, 7, 10, 3, 68, 40, 2, 23, 42, 18, 3, 19, 32);
//   w_t b (6, 20, 0, 0, 12, 7, 5, 27, 21, 0, 0, 13, 4, 1, 15, 0, 0, 4, 12, 13, 2, 6, 0, 7, 11, 0, 2, 3, 6, 0, 11, 29);
// //   w_t a (14, 83, 96, 22, 31, 55, 19, 99, 99, 96, 72, 98, 11, 80, 30, 1, 12, 64, 87, 50, 79, 36, 21, 68, 40, 74, 48, 42, 18, 30, 79, 32);
// //   w_t b (20, 62, 8, 44, 74, 47, 24, 63, 73, 19, 12, 37, 92, 9, 75, 55, 4, 44, 33, 63, 9, 26, 6, 75, 91, 72, 25, 45, 24, 27, 30, 93);
// //   w_t r = eve::gcd(a, b);
//      w_t r = a %b;
//      std::cout << r << std::endl;
//   }
   {
    w_t a (14);
    w_t b (0);
//   w_t a (14, 83, 96, 22, 31, 55, 19, 99, 99, 96, 72, 98, 11, 80, 30, 1, 12, 64, 87, 50, 79, 36, 21, 68, 40, 74, 48, 42, 18, 30, 79, 32);
//   w_t b (20, 62, 8, 44, 74, 47, 24, 63, 73, 19, 12, 37, 92, 9, 75, 55, 4, 44, 33, 63, 9, 26, 6, 75, 91, 72, 25, 45, 24, 27, 30, 93);
//   w_t r = eve::gcd(a, b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    w_t r = a %b;
     std::cout << r << std::endl;
  }

   TTS_EQUAL(0, 0);

}
