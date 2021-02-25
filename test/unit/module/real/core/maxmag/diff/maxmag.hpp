//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/maxmag.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(maxmag) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff_nth<2>(eve::maxmag)(T(), T()), T);
    TTS_EXPR_IS(eve::diff_nth<1>(eve::maxmag)(T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::maxmag) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::maxmag)(T{2},T{-3}), T(0));
    TTS_EQUAL(eve::diff_2nd(eve::maxmag)(T{2},T{-3}), T(1));
    TTS_EQUAL(eve::diff_1st(eve::maxmag)(T{-4},T{3}), T(1));
    TTS_EQUAL(eve::diff_2nd(eve::maxmag)(T{-4},T{3}), T(0));
    using v_t = eve::element_type_t<T>;
    TTS_EQUAL(eve::diff_1st(eve::maxmag)(T(1), T(2), T(3), T(4), T(5)),T(0));
    TTS_EQUAL(eve::diff_3rd(eve::maxmag)(T(1), T(2), T(10), T(4), T(5)),T(1));
    TTS_EQUAL(eve::diff_nth<3>(eve::maxmag)(T(1), T(2), T(3), T(4), T(5)),T(0));
    TTS_EQUAL(eve::diff_nth<6>(eve::maxmag)(T(1), T(2), T(3), T(4), T(5)),T(0));
    TTS_EQUAL(eve::diff_nth<4>(eve::maxmag)(v_t(1), T(3), T(3), T(7), T(5)),T(1));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
