//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fuzzy/trunc.hpp>
#include <eve/constant/eps.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::tolerant(eve::trunc) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(-1)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(-2)), T(-2));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(0)), T(0));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(1)), T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(2)), T(2));

    TTS_EQUAL(eve::tolerant(eve::trunc)(T(-1.3)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(-1.5)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(-1.6)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(1.3)) , T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(1.5)) , T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(1.6)) , T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(T(0)), T(0));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-eve::eps(eve::as<T>()))), T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-2*eve::eps(eve::as<T>()))), T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-3*eve::eps(eve::as<T>()))), T(1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-4*eve::eps(eve::as<T>()))), T(0));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(eve::eps(eve::as<T>()))), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(2*eve::eps(eve::as<T>()))), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(3*eve::eps(eve::as<T>()))), T(-1));
    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(4*eve::eps(eve::as<T>()))), T(0));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
