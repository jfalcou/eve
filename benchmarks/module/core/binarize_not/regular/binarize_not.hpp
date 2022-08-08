//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>

int main()
{
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE  = eve::logical<EVE_TYPE>;

  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);

  eve::bench::experiment xp;
  run<L_VALUE>(EVE_NAME(binarize_not) , xp, eve::binarize_not, arg0);
  run<L_TYPE> (EVE_NAME(binarize_not) , xp, eve::binarize_not, arg0);


}
