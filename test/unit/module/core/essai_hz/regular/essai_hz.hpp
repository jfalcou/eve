//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/any.hpp>
#include <eve/function/if_else.hpp>

TTS_CASE_TPL("Check eve::arg return type", EVE_TYPE)
{
  using eve::any;
  using elt_t = eve::element_type_t < T >;
  using w_t = eve::wide<elt_t, eve::fixed<8>>;
  auto f0 = [](auto ){return 0; };
  auto f1 = [](auto ){return 100; };
  auto f2 = [](auto ){return 2000; };
  auto f3 = [](auto ){return 30000; };
  auto f4 = [](auto ){return 400000;  };
  elt_t lim0 = 1;
  elt_t lim1 = 2;
  elt_t lim2 = 4;
  elt_t lim3 = 6;
//  elt_t lim4 = eve::inf(eve::as(lim0));
  w_t x{6.5, 1.3, 1.3, 2.5, 4.5, 7.8, 0.1, 3.4};
  w_t r(36);
  auto notdone = eve::true_(as(r));
  notdone = first_interval(f0, notdone, x < lim0, r, x);
  if(any(notdone)) notdone = next_interval(f1,  notdone, x < lim1, r, x);
//  std::cout << notdone << std::endl;
  if(any(notdone)) notdone = next_interval(f2,  notdone, x < lim2, r, x);
//   std::cout <<  notdone << std::endl;
  if(any(notdone)) notdone = next_interval(f3,  notdone, x < lim3, r, x);
//   std::cout << "bef kast " <<  notdone << std::endl;
  if(any(notdone)) last_interval(f4, notdone, r, x) ;
//   std::cout <<  notdone << std::endl;
//   std::cout << " ============================= " << std::endl;

  std::cout << "r " << r << std::endl;
  std::cout << " ============================= " << std::endl;
  w_t r2{400000, 100, 100, 2000, 30000, 400000, 0, 2000};
  TTS_IEEE_EQUAL(r2,r);
//   w_t r1(36);
//   (first_interval(f0, notdone, x < lim0, r1, x)&&
//    (next_interval(f2,  notdone, x < lim2, r1, x))&&
//    (next_interval(f3,  notdone, x < lim3, r1, x))&&
//    (last_interval(f4, notdone, r1, x)));
//   std::cout << "r1 " << r1 << std::endl;
//   std::cout << " ============================= " << std::endl;
//   TTS_IEEE_EQUAL(r2,r1);


}
