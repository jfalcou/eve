//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
#include <eve/module/core.hpp>
//==================================================================================================
#include "test.hpp"

TTS_CASE_TPL( "Check behavior of swap_if - scalar values"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
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

TTS_CASE_WITH( "Check behavior of swap_if - wide arithmetic"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0), tts::ramp(10), tts::logicals(1,2) )
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

TTS_CASE_WITH( "Check behavior of swap_if - logical"
        , eve::test::simd::all_types
        , tts::generate ( tts::logicals(1,2), tts::logicals(0,3), tts::logicals(1,2) )
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
