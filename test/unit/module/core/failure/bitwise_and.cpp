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
#include <eve/function/bitwise_and.hpp>

std::uint8_t a;
eve::wide<int,eve::fixed<4>> va;
eve::wide<int,eve::fixed<8>> vb;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto r1  = eve::bitwise_and(a   , 1ULL  );
auto r2  = eve::bitwise_and(va  , 1ULL  );
auto r3  = eve::bitwise_and(1ULL, va    );
auto r4  = eve::bitwise_and(va  , vb    );
auto r5  = eve::bitwise_and(vb  , va    );

