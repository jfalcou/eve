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

#include <tts/tests/relation.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check splatting constructor for logical wide", EVE_TYPE )
{
  eve::logical<T> from_bool_t{true};
  eve::logical<T> from_logical_t{eve::logical<T>(true)};
  eve::logical<T> from_value_t{EVE_VALUE{123}};

  eve::logical<T> from_bool_f{false};
  eve::logical<T> from_logical_f{eve::logical<T>(false)};
  eve::logical<T> from_value_f{EVE_VALUE{0}};

  eve::logical<T> all_t;
  eve::logical<T> all_f;

  for(std::size_t i = 0; i < EVE_CARDINAL; ++i)
  {
    all_t.set(i, true);
    all_f.set(i, false);
  }

  TTS_EQUAL(from_bool_t   , all_t);
  TTS_EQUAL(from_logical_t, all_t);
  TTS_EQUAL(from_value_t  , all_t);

  TTS_EQUAL(from_bool_f   , all_f);
  TTS_EQUAL(from_logical_f, all_f);
  TTS_EQUAL(from_value_f  , all_f);
}
