//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE_TPL("load behavior for scalar", EVE_TYPE)
{
  TTS_WHEN("A value is initialized")
  {
    T value, ref = 42, data[ 1 ] = {42};

    TTS_AND_THEN("we load a pointer to scalar")
    {
      value = eve::load(&ref);
      TTS_EQUAL(value, ref);
    }

    TTS_AND_THEN("we load an aligned pointer to scalar")
    {
      value = eve::load(eve::as_aligned(&ref));
      TTS_EQUAL(value, ref);
    }

    TTS_AND_THEN("we load a pointer to scalar values")
    {
      value = eve::load(&data[ 0 ], eve::as(value));
      TTS_EQUAL(value, ref);
    }

    TTS_AND_THEN("we load an aligned pointer to scalar values")
    {
      value = eve::load(eve::as_aligned(&data[ 0 ]), eve::as(value));
      TTS_EQUAL(value, ref);
    }
  }
}

#endif
