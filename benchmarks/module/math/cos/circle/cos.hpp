//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pi.hpp>

int main()
{
  auto lmax = eve::pi(eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin, lmax);
  auto std__cos = [](auto x){return std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(scalar std::cos)  , xp, std__cos                  , arg0);
  run<EVE_VALUE>(EVE_NAME(circle(cos)) , xp, eve::circle(eve::cos), arg0);
  run<EVE_TYPE >(EVE_NAME(circle(cos)) , xp, eve::circle(eve::cos), arg0);
}
