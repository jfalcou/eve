//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ffs.hpp>

TTS_CASE_TPL("Check ffs return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::ffs(T()), T);
}

TTS_CASE_TPL("Check eve::ffs behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::ffs(T(1)), T(0));
  TTS_EQUAL(eve::ffs(T(2)), T(1));
  TTS_EQUAL(eve::ffs(T(3)), T(0));
  TTS_EQUAL(eve::ffs(T(4)), T(2));
  TTS_EQUAL(eve::ffs(T(~0)), T(0));
  TTS_EQUAL(eve::ffs(T(1 << 4)), T(4));
  TTS_EQUAL(eve::ffs(T(elt_t(1) << (sizeof(elt_t)*8-1))), T(sizeof(elt_t)*8-1));
  TTS_EQUAL(eve::ffs(T(128)), T(7));
}
