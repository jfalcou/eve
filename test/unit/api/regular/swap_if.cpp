//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/swap_if.hpp>

EVE_TEST( "Check behavior of swap_if - arithmetic"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(0), eve::test::ramp(10), eve::test::logicals(1,2) )
        )
<typename T, typename L>(T lhs, T rhs, L mask)
{
  T swapped_lhs = [=](auto i, auto) { return mask.get(i) ? rhs.get(i) : lhs.get(i); };
  T swapped_rhs = [=](auto i, auto) { return mask.get(i) ? lhs.get(i) : rhs.get(i); };

  eve::swap_if(mask,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );
};

EVE_TEST( "Check behavior of swap_if - logical"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::logicals(1,2), eve::test::logicals(0,3), eve::test::logicals(1,2) )
        )
<typename L>(L lhs, L rhs, L mask)
{
  L swapped_lhs = [=](auto i, auto) { return mask.get(i) ? rhs.get(i) : lhs.get(i); };
  L swapped_rhs = [=](auto i, auto) { return mask.get(i) ? lhs.get(i) : rhs.get(i); };

  eve::swap_if(mask,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );
};
