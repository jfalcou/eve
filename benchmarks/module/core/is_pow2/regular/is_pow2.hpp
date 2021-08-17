//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <bit>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using ui_t =  eve::as_integer_t<EVE_VALUE, unsigned>;
  auto const std__is_pow2 = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return std::has_single_bit(ui_t(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_pow2) , xp, std__is_pow2, arg0);
  run<EVE_VALUE> (EVE_NAME(is_pow2) , xp, eve::is_pow2, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_pow2) , xp, eve::is_pow2, arg0);
}
