//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/function/bit_and.hpp>

std::uint8_t a;
eve::wide<int,eve::fixed<4>> va;
eve::wide<int,eve::fixed<8>> vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::bit_and(a   , 1ULL  );
auto r2  = eve::bit_and(va  , 1ULL  );
auto r3  = eve::bit_and(1ULL, va    );
auto r4  = eve::bit_and(va  , vb    );
auto r5  = eve::bit_and(vb  , va    );
