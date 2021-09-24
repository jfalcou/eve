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

EVE_TEST_TYPES( "Check behavior of swap_if - scalar values"
              , eve::test::scalar::all_types
              )
<typename T>(eve::as<T>)
{
  T lhs = 13;
  T rhs = 37;

  auto swapped_lhs = lhs;
  auto swapped_rhs = rhs;

  eve::swap_if(false,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );

  swapped_lhs = rhs;
  swapped_rhs = lhs;

  eve::swap_if(true,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );
};

EVE_TEST( "Check behavior of swap_if - wide arithmetic"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0), eve::test::ramp(10), eve::test::logicals(1,2) )
        )
<typename T, typename L>(T lhs, T rhs, L mask)
{
  auto swapped_lhs = lhs;
  auto swapped_rhs = rhs;

  eve::swap_if(false,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );

  swapped_lhs = rhs;
  swapped_rhs = lhs;

  eve::swap_if(true,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );

  swapped_lhs = T( [=](auto i, auto) { return mask.get(i) ? rhs.get(i) : lhs.get(i); } );
  swapped_rhs = T( [=](auto i, auto) { return mask.get(i) ? lhs.get(i) : rhs.get(i); } );

  eve::swap_if(mask,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );
};

EVE_TEST( "Check behavior of swap_if - logical"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::logicals(1,2), eve::test::logicals(0,3), eve::test::logicals(1,2) )
        )
<typename L>(L lhs, L rhs, L mask)
{
  auto swapped_lhs = lhs;
  auto swapped_rhs = rhs;

  eve::swap_if(false,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );

  swapped_lhs = rhs;
  swapped_rhs = lhs;

  eve::swap_if(true,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );

  swapped_lhs = L([=](auto i, auto) { return mask.get(i) ? rhs.get(i) : lhs.get(i); });
  swapped_rhs = L([=](auto i, auto) { return mask.get(i) ? lhs.get(i) : rhs.get(i); });

  eve::swap_if(mask,lhs,rhs);

  TTS_EQUAL( swapped_lhs, lhs );
  TTS_EQUAL( swapped_rhs, rhs );
};
