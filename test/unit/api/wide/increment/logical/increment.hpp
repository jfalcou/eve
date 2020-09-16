//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/wide.hpp>
#include <eve/logical.hpp>

using eve::fixed;
using eve::logical;
using eve::wide;

logical<wide<EVE_TYPE, fixed<1>>>  x1;
logical<wide<EVE_TYPE, fixed<2>>>  x2;
logical<wide<EVE_TYPE, fixed<4>>>  x4;
logical<wide<EVE_TYPE, fixed<8>>>  x8;
logical<wide<EVE_TYPE, fixed<16>>> x16;
logical<wide<EVE_TYPE, fixed<32>>> x32;
logical<wide<EVE_TYPE, fixed<64>>> x64;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto pre1  = ++x1;
auto pre2  = ++x2;
auto pre4  = ++x4;
auto pre8  = ++x8;
auto pre16 = ++x16;
auto pre32 = ++x32;
auto pre64 = ++x64;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto post1  = x1++;
auto post2  = x2++;
auto post4  = x4++;
auto post8  = x8++;
auto post16 = x16++;
auto post32 = x32++;
auto post64 = x64++;
