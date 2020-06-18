//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log10.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmax = eve::Valmax<EVE_VALUE>();
  EVE_REGISTER_BENCHMARK(eve::log10, EVE_TYPE, eve::bench::random<EVE_TYPE>(EVE_VALUE(0), lmax));

}
