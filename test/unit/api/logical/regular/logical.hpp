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

#include <eve/constant/allbits.hpp>
#include <eve/logical.hpp>

#if !defined(EVE_SIMD_TESTS)
TTS_CASE_TPL("logical constructors", EVE_TYPE)
{
  eve::logical<T> empty;
  eve::logical<T> from_bool_t = true;
  eve::logical<T> from_bool_f = false;
  eve::logical<T> from_value_t(T{123});
  eve::logical<T> from_value_f(T{0});

  TTS_EXPECT((bool(empty) == false || bool(empty) == true));

  TTS_EXPECT(from_bool_t);
  TTS_EXPECT(from_value_t);

  TTS_EXPECT_NOT(from_value_f);
  TTS_EXPECT_NOT(from_bool_f);
}

TTS_CASE_TPL("logical assignment", EVE_TYPE)
{
  eve::logical<T> from_bool_t;
  from_bool_t = true;

  eve::logical<T> from_bool_f;
  from_bool_f = false;

  eve::logical<T> from_value_t;
  from_value_t = T{123};

  eve::logical<T> from_value_f;
  from_value_f = T{0};

  TTS_EXPECT(from_bool_t);
  TTS_EXPECT(from_value_t);

  TTS_EXPECT_NOT(from_value_f);
  TTS_EXPECT_NOT(from_bool_f);
}
#endif

/*
TTS_CASE_TPL("logical assignments", EVE_TYPE)
{
  eve::logical<T> empty_t;
  eve::logical<T> empty_f;

  empty_t = true;
  TTS_EXPECT(empty_t);

  empty_f = false;
  TTS_EXPECT_NOT(empty_f);
}

TTS_CASE_TPL("logical->bool conversion", EVE_TYPE)
{
  eve::logical<T> bool_t = true;
  eve::logical<T> bool_f = false;

  TTS_EXPECT(bool(bool_t));
  TTS_EXPECT(bool_t.value());
  TTS_EXPECT_NOT(bool(bool_f));
  TTS_EXPECT_NOT(bool_f.value());
}
*/

TTS_CASE_TPL("logical mask conversion", EVE_TYPE)
{
  eve::logical<T> bool_t{true};
  eve::logical<T> bool_f{false};

  TTS_EQUAL(bool_f.mask(), T(0));
  TTS_IEEE_EQUAL(bool_t.mask(), eve::allbits(eve::as<T>()));
}

TTS_CASE_TPL("logical bits conversion", EVE_TYPE)
{
  eve::logical<T> bool_t{true};
  eve::logical<T> bool_f{false};

  using bits_t = typename eve::logical<T>::bits_type;

  TTS_EQUAL(bool_f.bits(), bits_t(0));
  TTS_IEEE_EQUAL(bool_t.bits(), eve::allbits(eve::as<bits_t>()));
}


#if defined(EVE_SIMD_TESTS)
TTS_CASE_TPL("logical getters and setters", EVE_TYPE)
{
  eve::logical<T> x{false};

  for (int i = 0; i != T::static_size; ++i) {
    TTS_EXPECT_NOT(x[i]);
    x.set(i, true);
    TTS_EXPECT(x[i]);
    x.set(i, false);
    TTS_EXPECT_NOT(x[i]);
  }
}
#endif
