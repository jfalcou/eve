//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOAD_HPP
#define LOAD_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/load.hpp>

using eve::fixed;

TTS_CASE("load behavior for scalar")
{
  TTS_SETUP("load a scalar from")
  {
    Type value, ref = 42, data[ 1 ] = {42};

    TTS_SECTION("a pointer to scalar")
    {
      value = eve::load(&ref);
      TTS_EQUAL(value, ref);
    }

    TTS_SECTION("an aligned pointer to scalar")
    {
      value = eve::load(eve::as_aligned(&ref));
      TTS_EQUAL(value, ref);
    }

    TTS_SECTION("a pointer to scalar values")
    {
      value = eve::load(&data[ 0 ], eve::as(value));
      TTS_EQUAL(value, ref);
    }

    TTS_SECTION("an aligned pointer to scalar values")
    {
      value = eve::load(eve::as_aligned(&data[ 0 ]), eve::as(value));
      TTS_EQUAL(value, ref);
    }
  }
}

#endif
