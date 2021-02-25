//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fls.hpp>

TTS_CASE_TPL("Check fls return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::fls(T()), T);
}

TTS_CASE_TPL("Check eve::fls behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::fls(T(1)), T(0));
  TTS_EQUAL(eve::fls(T(2)), T(1));
  TTS_EQUAL(eve::fls(T(3)), T(1));
  TTS_EQUAL(eve::fls(T(4)), T(2));
  TTS_EQUAL(eve::fls(T(~0)), T(sizeof(elt_t)*8-1));
  TTS_EQUAL(eve::fls(T(1 << 4)), T(4));
  TTS_EQUAL(eve::fls(T(elt_t(1) << (sizeof(elt_t)*8-1))), T(sizeof(elt_t)*8-1));
}
