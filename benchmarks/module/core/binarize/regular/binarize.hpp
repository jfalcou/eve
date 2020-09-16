//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize.hpp>

int main()
{
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE  = eve::logical<EVE_TYPE>;

  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);

  eve::bench::experiment xp;
  run<L_VALUE>(EVE_NAME(binarize) , xp, eve::binarize, arg0);
  run<L_TYPE> (EVE_NAME(binarize) , xp, eve::binarize, arg0);


}
