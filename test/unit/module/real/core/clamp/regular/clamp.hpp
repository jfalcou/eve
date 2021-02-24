//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/clamp.hpp>

TTS_CASE_TPL("Check eve::clamp return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::clamp(T(), T() , T()) , T);
  TTS_EXPR_IS(eve::clamp(T(), v_t(), T()) , T);
  TTS_EXPR_IS(eve::clamp(T(), T() , v_t()), T);
  TTS_EXPR_IS(eve::clamp(T(), v_t(), v_t()), T);
}

TTS_CASE_TPL("Check eve::clamp behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::clamp(T(1), T(2) , T(4))  , T(2));
  TTS_EQUAL(eve::clamp(T(1), v_t(2), T(4))  , T(2));
  TTS_EQUAL(eve::clamp(T(1), T(2) , v_t(4)) , T(2));
  TTS_EQUAL(eve::clamp(T(1), v_t(2), v_t(4)) , T(2));

  TTS_EQUAL(eve::clamp(T(2), T(2), T(4)), T(2));
  TTS_EQUAL(eve::clamp(T(2), v_t(2), T(4)), T(2));
  TTS_EQUAL(eve::clamp(T(2), T(2), v_t(4)), T(2));
  TTS_EQUAL(eve::clamp(T(2), v_t(2), v_t(4)), T(2));

  TTS_EQUAL(eve::clamp(T(3), T(2), T(4)), T(3));
  TTS_EQUAL(eve::clamp(T(3), v_t(2), T(4)), T(3));
  TTS_EQUAL(eve::clamp(T(3), T(2), v_t(4)), T(3));
  TTS_EQUAL(eve::clamp(T(3), v_t(2), v_t(4)), T(3));

  TTS_EQUAL(eve::clamp(T(4), T(2), T(4)), T(4));
  TTS_EQUAL(eve::clamp(T(4), v_t(2), T(4)), T(4));
  TTS_EQUAL(eve::clamp(T(4), T(2), v_t(4)), T(4));
  TTS_EQUAL(eve::clamp(T(4), v_t(2), v_t(4)), T(4));

  TTS_EQUAL(eve::clamp(T(5), T(2), T(4)), T(4));
  TTS_EQUAL(eve::clamp(T(5), v_t(2), T(4)), T(4));
  TTS_EQUAL(eve::clamp(T(5), T(2), v_t(4)), T(4));
  TTS_EQUAL(eve::clamp(T(5), v_t(2), v_t(4)), T(4));
}
