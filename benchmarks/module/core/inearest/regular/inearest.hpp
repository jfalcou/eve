//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  using I_VALUE = eve::detail::as_integer_t<EVE_VALUE>;

  auto const std__inearest = [](EVE_VALUE x) { return static_cast<I_VALUE>(std::ceil(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE> (EVE_NAME(std__inearest) , xp, std__inearest, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::int_(eve::ceil)) , xp, eve::int_(eve::ceil), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::int_(eve::ceil)) , xp, eve::int_(eve::ceil), arg0);
}
