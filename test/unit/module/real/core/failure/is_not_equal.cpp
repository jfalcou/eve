//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
