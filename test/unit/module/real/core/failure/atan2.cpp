//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/atan2.hpp>

int a, b;
eve::wide<int> va, vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::atan2(a, b);
auto r2  = eve::atan2(va, vb);
