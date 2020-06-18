//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecd.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  EVE_REGISTER_BENCHMARK(eve::asecd, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(EVE_VALUE(1), eve::Valmax<EVE_VALUE>()));

}
