//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/fls.hpp>

TTS_CASE_TPL("Check pedantic fls return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::fls)(T()), T);
}

TTS_CASE_TPL("Check pedantic eve::fls behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::pedantic(eve::fls)(T(0)), T(sizeof(elt_t)*8));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(1)), T(0));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(2)), T(1));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(3)), T(1));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(4)), T(2));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(~0)), T(sizeof(elt_t)*8-1));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(1 << 4)), T(4));
  TTS_EQUAL(eve::pedantic(eve::fls)(T(elt_t(1) << (sizeof(elt_t)*8-1))), T(sizeof(elt_t)*8-1));
}
