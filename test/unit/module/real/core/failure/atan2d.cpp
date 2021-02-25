//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/atan2d.hpp>

int a, b;
eve::wide<int> va, vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::atan2d(a, b);
auto r2  = eve::atan2d(va, vb);
