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
#include <eve/function/bit_cast.hpp>

int a;
eve::wide<int,eve::fixed<4>> va;
eve::wide<int,eve::fixed<8>> vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::bit_cast(a , eve::int8_ );
auto r2  = eve::bit_cast(a , as(vb)     );
auto r3  = eve::bit_cast(va, eve::int8_ );
auto r4  = eve::bit_cast(va, as(vb)     );

