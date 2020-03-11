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
#include <eve/function/hypot.hpp>

int a, b;
eve::wide<int> va, vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::hypot(a, b);
auto r2  = eve::hypot(va, vb);

