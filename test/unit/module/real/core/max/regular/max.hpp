//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>

TTS_CASE_TPL("Check eve::max return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::max(T(0)   , T(0) ) , T);
  TTS_EXPR_IS(eve::max(v_t(0) , T(0) ) , T);
  TTS_EXPR_IS(eve::max(T(0)   , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::max behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::max(T(0), T(0)), T(0));
  TTS_EQUAL(eve::max(T(0), T(1)), T(1));
  TTS_EQUAL(eve::max(T(1), T(0)), T(1));
  TTS_EQUAL(eve::max(T(1), T(1)), T(1));

  TTS_EQUAL(eve::max(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::max(v_t(0), T(1)), T(1));
  TTS_EQUAL(eve::max(v_t(1), T(0)), T(1));
  TTS_EQUAL(eve::max(v_t(1), T(1)), T(1));

  TTS_EQUAL(eve::max(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::max(T(0), v_t(1)), T(1));
  TTS_EQUAL(eve::max(T(1), v_t(0)), T(1));
  TTS_EQUAL(eve::max(T(1), v_t(1)), T(1));

  if constexpr (std::is_unsigned_v<v_t>)
  {
    TTS_EQUAL(eve::max(T(-1), v_t(1)), T(-1));
  }
  else
  {
    TTS_EQUAL(eve::max(T(-1), v_t(1)), T(1));
  }
}
