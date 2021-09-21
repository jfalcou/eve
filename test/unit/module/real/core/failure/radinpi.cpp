//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/radinpi.hpp>

int a;
eve::wide<int> va;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::radinpi(a);
auto r2  = eve::radinpi(va);
