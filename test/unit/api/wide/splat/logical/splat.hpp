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
#include <tts/tests/relation.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check splatting constructor for logical wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  eve::logical<eve::wide<EVE_TYPE, T>> from_bool_t{true};
  eve::logical<eve::wide<EVE_TYPE, T>> from_logical_t{eve::logical<EVE_TYPE>(true)};
  eve::logical<eve::wide<EVE_TYPE, T>> from_value_t{EVE_TYPE{123}};

  eve::logical<eve::wide<EVE_TYPE, T>> from_bool_f{false};
  eve::logical<eve::wide<EVE_TYPE, T>> from_logical_f{eve::logical<EVE_TYPE>(false)};
  eve::logical<eve::wide<EVE_TYPE, T>> from_value_f{EVE_TYPE{0}};

  eve::logical<eve::wide<EVE_TYPE, T>> all_t;
  eve::logical<eve::wide<EVE_TYPE, T>> all_f;

  for(std::size_t i = 0; i < T::value; ++i)
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
