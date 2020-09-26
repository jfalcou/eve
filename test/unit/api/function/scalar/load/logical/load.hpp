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

#include "test.hpp"
#include <eve/function/load.hpp>
#include <eve/logical.hpp>

using eve::fixed;
using eve::logical;

TTS_CASE_TPL("load behavior for scalar logical", EVE_TYPE)
{
  TTS_WHEN("A value is initialized")
  {
    logical<T> value, ref = true, data[ 1 ] = {true};

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
