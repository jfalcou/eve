//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOAD_HPP
#define LOAD_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/load.hpp>
#include <eve/logical.hpp>

using eve::fixed;
using eve::logical;

TTS_CASE("load behavior for scalar logical")
{
  TTS_SETUP("load a scalar from")
  {
    logical<Type> value, ref = true, data[ 1 ] = {true};

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
