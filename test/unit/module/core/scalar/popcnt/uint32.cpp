//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#include <eve/function/scalar/popcnt.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE( "Check popcnt correctness on 32 bits unsigned integrals" )
{
  using eve::popcnt;

  TTS_EQUAL( popcnt(std::uint32_t{0})         ,  0UL);
  TTS_EQUAL( popcnt(std::uint32_t{0xFFFFFFFF}), 32UL);
  TTS_EQUAL( popcnt(std::uint32_t{0xAAAAAAAA}), 16UL);
}
