//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/function/iota.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on pow_abs")
{
  auto std_pow_abs = [](auto e) { return eve::pow_abs(e, EVE_VALUE(10.51)); };
  auto  my_pow_abs = [](auto e) {  return eve::pedantic(eve::pow_abs)(e,  EVE_VALUE(10.51)); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0.05), EVE_VALUE(100.0));
  TTS_RANGE_CHECK_WITH(p, std_pow_abs, my_pow_abs, 8);

  auto std_pow_abs1 = [](auto e) { return eve::pow_abs(EVE_VALUE(0.51), e); };
  auto  my_pow_abs1 = [](auto e) {  return eve::pedantic(eve::pow_abs)(EVE_VALUE(0.51), e); };

  eve::uniform_prng<EVE_VALUE> p1(EVE_VALUE(0.05), EVE_VALUE(10.5));
  TTS_RANGE_CHECK_WITH(p1, std_pow_abs1, my_pow_abs1, 8);
}
