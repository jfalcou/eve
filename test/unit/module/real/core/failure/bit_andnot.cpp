//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/bit_andnot.hpp>

int a,b,x;
eve::wide<int> va,vb,vx;
eve::wide<char> ca
eve::logical<int> t; 
//==================================================================================================
// None of those should compiles
//==================================================================================================
auto ban_s  = eve::bit_andnot[  x < 0 ]( a,  b);
auto ban_v  = eve::bit_andnot[ vx < 0 ](va, vb);
auto ban_ci = eve::bit_andnot(va, ca);
auto ban_l  = eve::bit_andnot(va, t); 
