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
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using I_VALUE = eve::detail::as_integer_t<EVE_VALUE>;

  auto const std__iceil = [](EVE_VALUE x) { return static_cast<I_VALUE>(std::ceil(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__iceil) , xp, std__iceil, arg0);
  run<EVE_VALUE> (EVE_NAME(int_(eve::ceil)) , xp, eve::int_(eve::ceil), arg0);
  run<EVE_TYPE>  (EVE_NAME(int_(eve::ceil)) , xp, eve::int_(eve::ceil), arg0);
}
