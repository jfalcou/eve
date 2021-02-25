//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fuzzy/ceil.hpp>
#include <eve/constant/eps.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::tolerant(eve::ceil) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(-2)), T(-2));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(0)), T(0));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(1)), T(1));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(2)), T(2));

    TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.3)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.5)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.6)), T(-1));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.3)) , T(2));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.5)) , T(2));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.6)) , T(2));
    TTS_EQUAL(eve::tolerant(eve::ceil)(T(0)), T(0));
    TTS_EQUAL(eve::tolerant(eve::ceil)(eve::eps(eve::as<T>())), T(0));
    TTS_EQUAL(eve::tolerant(eve::ceil)(2*eve::eps(eve::as<T>())), T(0));
    TTS_EQUAL(eve::tolerant(eve::ceil)(3*eve::eps(eve::as<T>())), T(0));
    TTS_EQUAL(eve::tolerant(eve::ceil)(4*eve::eps(eve::as<T>())), T(1));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
