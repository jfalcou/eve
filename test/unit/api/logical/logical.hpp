//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <tts/tests/precision.hpp>
#include <eve/logical.hpp>
#include <eve/constant/allbits.hpp>

TTS_CASE("logical constructors")
{
  eve::logical<EVE_TYPE> empty;
  eve::logical<EVE_TYPE> from_bool_t = true;
  eve::logical<EVE_TYPE> from_bool_f = false;
  eve::logical<EVE_TYPE> from_value_t(EVE_TYPE{123});
  eve::logical<EVE_TYPE> from_value_f(EVE_TYPE{0});

  TTS_EXPECT((bool(empty) == false || bool(empty) == true));

  TTS_EXPECT(from_bool_t);
  TTS_EXPECT(from_value_t);

  TTS_EXPECT_NOT(from_value_f);
  TTS_EXPECT_NOT(from_bool_f);
}

TTS_CASE("logical assignments")
{
  eve::logical<EVE_TYPE> empty_t;
  eve::logical<EVE_TYPE> empty_f;

  empty_t = true;
  TTS_EXPECT(empty_t);

  empty_f = false;
  TTS_EXPECT_NOT(empty_f);
}

TTS_CASE("logical->bool conversion")
{
  eve::logical<EVE_TYPE> bool_t = true;
  eve::logical<EVE_TYPE> bool_f = false;

  TTS_EXPECT(bool(bool_t));
  TTS_EXPECT(bool_t.value());
  TTS_EXPECT_NOT(bool(bool_f));
  TTS_EXPECT_NOT(bool_f.value());
}

TTS_CASE("logical mask conversion")
{
  eve::logical<EVE_TYPE> bool_t = true;
  eve::logical<EVE_TYPE> bool_f = false;

  TTS_IEEE_EQUAL(bool_t.mask(), eve::Allbits<EVE_TYPE>());
  TTS_IEEE_EQUAL(bool_f.mask(), EVE_TYPE(0));
}

TTS_CASE("logical bits conversion")
{
  eve::logical<EVE_TYPE> bool_t = true;
  eve::logical<EVE_TYPE> bool_f = false;
  using bits_t              = eve::logical<EVE_TYPE>::bits_type;

  TTS_IEEE_EQUAL(bool_t.bits(), eve::Allbits<bits_t>());
  TTS_IEEE_EQUAL(bool_f.bits(), bits_t(0));
}

#endif
