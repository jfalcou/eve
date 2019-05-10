//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INCREMENT_HPP
#define INCREMENT_HPP

#include <eve/wide.hpp>
#include <eve/logical.hpp>

using eve::fixed;
using eve::wide;
using eve::logical;

logical<wide<Type, fixed< 1>>> x1;
logical<wide<Type, fixed< 2>>> x2;
logical<wide<Type, fixed< 4>>> x4;
logical<wide<Type, fixed< 8>>> x8;
logical<wide<Type, fixed<16>>> x16;
logical<wide<Type, fixed<32>>> x32;
logical<wide<Type, fixed<64>>> x64;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto pre1   = ++x1;
auto pre2   = ++x2;
auto pre4   = ++x4;
auto pre8   = ++x8;
auto pre16  = ++x16;
auto pre32  = ++x32;
auto pre64  = ++x64;

//==================================================================================================
// None of those should compiles
//==================================================================================================
auto post1   = x1++;
auto post2   = x2++;
auto post4   = x4++;
auto post8   = x8++;
auto post16  = x16++;
auto post32  = x32++;
auto post64  = x64++;

#endif
