//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pio_4.hpp>

int main()
{
  auto lmax = eve::pio_4(eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin, lmax);
  auto std__cos = [](auto x){return std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(scalar std::cos)  , xp, std__cos                  , arg0);
  run<EVE_VALUE>(EVE_NAME(restricted(cos)) , xp, eve::restricted(eve::cos), arg0);
  run<EVE_TYPE >(EVE_NAME(restricted(cos)) , xp, eve::restricted(eve::cos), arg0);
}
