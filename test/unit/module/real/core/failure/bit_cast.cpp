//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
auto r1  = eve::bit_cast(a , eve::int8 );
auto r2  = eve::bit_cast(a , as(vb)     );
auto r3  = eve::bit_cast(va, eve::int8 );
auto r4  = eve::bit_cast(va, as(vb)     );
