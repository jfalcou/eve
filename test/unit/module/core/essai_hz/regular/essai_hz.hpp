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
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/detail/horizontal_choices.hpp>

TTS_CASE_TPL("Check eve::arg return type", EVE_TYPE)
{
  using eve::detail::hz_device;
  using elt_t = eve::element_type_t < T >;
  using w_t = eve::wide<elt_t, eve::fixed<8>>;
  auto f0 = [](auto x){return x; };
  auto f1 = [](auto x){return x+100; };
  auto f2 = [](auto x){return x+2000; };
  auto f3 = [](auto x){return x+30000; };
  auto f4 = [](auto x){return x+400000;  };
  elt_t lim0 = 1;
  elt_t lim1 = 2;
  elt_t lim2 = 4;
  elt_t lim3 = 6;
//  elt_t lim4 = eve::inf(eve::as(lim0));
  w_t x{2.5, 1.3, 1.3, 2.5, 4.5, 7.8, 0.1, 3.4};
  hz_device < w_t> hz(36);
  hz.first_interval(f0, lim0, x) &&
    hz.next_interval(f1, lim1)&&
    hz.next_interval(f2, lim2)&&
    hz.last_interval(f3, f4, lim3);

  std::cout << hz.result() << std::endl;
  std::cout << " ============================= " << std::endl;
  w_t r{2002.5, 101.3, 101.3, 2002.5, 30004.5, 400007.8, 0.1, 2003.4};
  TTS_IEEE_EQUAL(r,hz.result());

  hz_device < elt_t> hz1;
  hz1.first_interval(f0, lim0, 2.5);
  if (hz1.notdone()) {std::cout << 1 << std::endl; hz1.next_interval(f1, lim1); }
  if (hz1.notdone()) {std::cout << 2 << std::endl; hz1.next_interval(f2, lim2); }
  if (hz1.notdone()) {std::cout << 3 << std::endl; hz1.last_interval(f3, f4, lim3); }
  std::cout << hz1.result() << std::endl;


}
