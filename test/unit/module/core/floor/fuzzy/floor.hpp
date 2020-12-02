//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fuzzy/floor.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>


TTS_CASE_TPL("Check eve::tolerant(eve::floor) behavior", EVE_TYPE)
{
  using eve::as;
  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(-1.3)), T(-2));
   TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(-1.5)), T(-2));
   TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(-1.6)), T(-2));
   TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(1.3)) , T( 1));
   TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(1.5)) , T( 1));
   TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(1.6)) , T( 1));

    auto epsi = eve::eps(eve::as<T>());
   TTS_EQUAL(eve::tolerant(eve::floor)(T(0)), T(0));
   TTS_EQUAL(eve::tolerant(eve::floor)(-epsi), T(0));
   TTS_EQUAL(eve::tolerant(eve::floor)((-2*epsi)), T(0));
   TTS_EQUAL(eve::tolerant(eve::floor)((-3*epsi)), T(0));
   TTS_EQUAL(eve::tolerant(eve::floor)((-4*epsi)), T(-1));

   TTS_EQUAL(eve::tolerant(eve::floor)(T(1)), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-epsi)), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-2*epsi)), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-3*epsi)), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-4*epsi)), T(0));

   TTS_EQUAL(eve::tolerant(eve::floor)(T(45)), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(45*(T(1)-2*epsi)), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(45*(T(1)-3*epsi)), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(45*(T(1)-4*epsi)), T(44));


   TTS_EQUAL(eve::tolerant(eve::floor)(T(1)), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 1), 3), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 2), 3), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 3), 3), T(1));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 4), 3), T(0));

   TTS_EQUAL(eve::tolerant(eve::floor)(T(45)), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 1), 3), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 2), 3), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 3), 3), T(45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 4), 3), T(44));

   TTS_EQUAL(eve::tolerant(eve::floor)(T(-45)), T(-45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 1), 3), T(-45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 2), 3), T(-45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 3), 3), T(-45));
   TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 4), 3), T(-46));


  }
}
