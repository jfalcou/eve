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
#include <eve/function/ldexp.hpp>

int a, b;
eve::wide<int> va, vb;


//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::ldexp(a, b);
auto r2  = eve::ldexp(va, vb);

