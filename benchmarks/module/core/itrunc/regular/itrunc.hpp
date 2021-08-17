//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using I_VALUE = eve::as_integer_t<EVE_VALUE>;

  auto const std__itrunc = [](EVE_VALUE x) { return static_cast<I_VALUE>(std::ceil(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__itrunc) , xp, std__itrunc, arg0);
  run<EVE_VALUE> (EVE_NAME(int_(eve::ceil)) , xp, eve::int_(eve::ceil), arg0);
  run<EVE_TYPE>  (EVE_NAME(int_(eve::ceil)) , xp, eve::int_(eve::ceil), arg0);
}
