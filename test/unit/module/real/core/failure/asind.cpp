//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/asind.hpp>

int a;
eve::wide<int> va;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::asind(a);
auto r2  = eve::asind(va);
