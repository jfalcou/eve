//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/average.hpp>

TTS_CASE_TPL("Check eve::average return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using v_t = eve::element_type_t<T>;
    TTS_EXPR_IS(eve::average(T(), T(), T(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), T(), T()), T);
    TTS_EXPR_IS(eve::average(T(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(T(), T(), v_t(), v_t() ), T);
    TTS_EXPR_IS(eve::average(T(), T(), v_t(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), T(), v_t(), v_t(), T()), T);
  }
  else
    TTS_EQUAL(0, 0);
}

TTS_CASE_TPL("Check eve::average behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using v_t = eve::element_type_t<T>;

    TTS_EQUAL(eve::average(T{0}, T{0}, T{0}), T(0));
    TTS_EQUAL(eve::average(T{1}, T{1}, T{1}), T(1));
    TTS_EQUAL(eve::average(T{2}, T{2}, T{4}), T(8.0/3));

    TTS_EQUAL(eve::average(v_t{0}, T{0}, T{0}), T(0));
    TTS_EQUAL(eve::average(v_t{1}, T{1}, T{4}), T(2));
    TTS_EQUAL(eve::average(v_t{2}, T{2}, T{1}), T(5.0/3));

     TTS_EQUAL(eve::average(T{0}, T{0}, v_t{0}), T(0));
     TTS_EQUAL(eve::average(T{1}, T{4}, v_t{1}), T(2));
     TTS_EQUAL(eve::average(T{2}, T{1}, v_t{2}), T(5.0/3));


    TTS_EQUAL(eve::raw(eve::average)(T{0}, T{0}, T{0}), T(0));
    TTS_EQUAL(eve::raw(eve::average)(T{1}, T{1}, T{1}), T(1));
    TTS_EQUAL(eve::raw(eve::average)(T{2}, T{2}, T{4}), T(8.0/3));

    TTS_EQUAL(eve::raw(eve::average)(v_t{0}, T{0}, T{0}), T(0));
    TTS_EQUAL(eve::raw(eve::average)(v_t{1}, T{1}, T{4}), T(2));
    TTS_EQUAL(eve::raw(eve::average)(v_t{2}, T{2}, T{1}), T(5.0/3));

    TTS_EQUAL(eve::raw(eve::average)(T{0}, T{0}, v_t{0}), T(0));
    TTS_EQUAL(eve::raw(eve::average)(T{1}, T{4}, v_t{1}), T(2));
    TTS_EQUAL(eve::raw(eve::average)(T{2}, T{1}, v_t{2}), T(5.0/3));
  }
  else
    TTS_EQUAL(0, 0);
}
