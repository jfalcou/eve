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
#include <eve/function/bitwise_cast.hpp>

int a;
eve::wide<int,eve::fixed<4>> va;
eve::wide<int,eve::fixed<8>> vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::bitwise_cast(a , eve::int8_ );
auto r2  = eve::bitwise_cast(a , as(vb)     );
auto r3  = eve::bitwise_cast(va, eve::int8_ );
auto r4  = eve::bitwise_cast(va, as(vb)     );

