//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/is_not_equal.hpp>

int a,b,x;
eve::wide<int> va,vb,vx;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto is_eqs  = eve::is_not_equal[  x < 0 ]( a,  b);
auto is_eqv  = eve::is_not_equal[ vx < 0 ](va, vb);
