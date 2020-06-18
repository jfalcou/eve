//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acoth.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  EVE_REGISTER_BENCHMARK(eve::acoth, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(EVE_VALUE(1), eve::Valmax<EVE_VALUE>()));

}
