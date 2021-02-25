//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>


TTS_CASE_TPL("Check eve::add return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::add(T(), T()), T);
}

TTS_CASE_TPL("Check eve::add behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::add(T{0}, T{0}), T(0));
  TTS_EQUAL(eve::add(T{1}, T{1}), T(2));
  TTS_EQUAL(eve::add(T{2}, T{2}), T(4));

  TTS_EQUAL(eve::add(v_t{0}, T{0}), T(0));
  TTS_EQUAL(eve::add(v_t{1}, T{1}), T(2));
  TTS_EQUAL(eve::add(v_t{2}, T{2}), T(4));

  TTS_EQUAL(eve::add(T{0}, v_t{0}), T(0));
  TTS_EQUAL(eve::add(T{1}, v_t{1}), T(2));
  TTS_EQUAL(eve::add(T{2}, v_t{2}), T(4));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::add(T(-1), T(1)), T(0));
    TTS_EQUAL(eve::add(T(-2), T(-6)), T(-8));

    TTS_EQUAL(eve::add(v_t(-1), T(1)), T(0));
    TTS_EQUAL(eve::add(v_t(-2), T(-6)), T(-8));

    TTS_EQUAL(eve::add(T(-1), v_t(1)), T(0));
    TTS_EQUAL(eve::add(T(-2), v_t(-6)), T(-8));
  }
}
