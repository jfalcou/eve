//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_rshl.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  using I_TYPE    = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  using I_VALUE   = eve::detail::as_integer_t<EVE_VALUE, signed>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  auto smax = I_VALUE(sizeof(EVE_VALUE)-1);
  auto smin = I_VALUE(-smax);

  auto std__bit_rshl =  [](EVE_VALUE x,  I_VALUE y){return EVE_VALUE(y > 0 ? x << y : x >> -y); };
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(smin,smax);

  eve::bench::experiment xp;
  run<eve::bench::types<EVE_VALUE, I_VALUE>>(EVE_NAME(std__bit_rshl) , xp, std__bit_rshl, arg0, arg1);
  run<eve::bench::types<EVE_VALUE, I_VALUE>>(EVE_NAME(bit_rshl) , xp, eve::bit_rshl, arg0, arg1);
  run<eve::bench::types<EVE_TYPE,  I_VALUE>> (EVE_NAME(bit_rshl) , xp, eve::bit_rshl, arg0, arg1);
  run<eve::bench::types<EVE_TYPE,  I_TYPE>> (EVE_NAME(bit_rshl) , xp, eve::bit_rshl, arg0, arg1);


}
