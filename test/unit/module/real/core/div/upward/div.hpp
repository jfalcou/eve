//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE_TPL("Check div return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::upward(eve::div)(   T() ,   T()), T);
  TTS_EXPR_IS(eve::upward(eve::div)(   T() , v_t()), T);
  TTS_EXPR_IS(eve::upward(eve::div)( v_t() ,   T()), T);
}

TTS_CASE_TPL("Check eve::div behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::upward(eve::div)(   T(-1) ,   T(2)), T(0));
    TTS_EQUAL(eve::upward(eve::div)( v_t(-1) ,   T(2)), T(0));
    TTS_EQUAL(eve::upward(eve::div)(   T(-1) , v_t(2)), T(0));
  }

  TTS_EQUAL(eve::upward(eve::div)(T(12), T(4)), T(3));
  TTS_EQUAL(eve::upward(eve::div)(T(1) , T(2)), T(1));
  TTS_EQUAL(eve::upward(eve::div)(T(4) , T(3)), T(2));

  TTS_EQUAL(eve::upward(eve::div)(v_t(12), T(4)), T(3));
  TTS_EQUAL(eve::upward(eve::div)(v_t(1) , T(2)), T(1));
  TTS_EQUAL(eve::upward(eve::div)(v_t(4) , T(3)), T(2));

  TTS_EQUAL(eve::upward(eve::div)(T(12), v_t(4)), T(3));
  TTS_EQUAL(eve::upward(eve::div)(T(1) , v_t(2)), T(1));
  TTS_EQUAL(eve::upward(eve::div)(T(4) , v_t(3)), T(2));
}
