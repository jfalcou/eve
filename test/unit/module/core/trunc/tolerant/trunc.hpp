//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/trunc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/prev.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::tolerant(eve::trunc) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::tolerant(eve::trunc)(T()), T);
}

TTS_CASE_TPL("Check eve::tolerant(eve::trunc) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::tolerant(eve::trunc)(T(0)), T(0) );
  TTS_EQUAL(eve::tolerant(eve::trunc)(T(1)), T(1) );
  TTS_EQUAL(eve::tolerant(eve::trunc)(T(2)), T(2) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>(-1)), T(-1) );
    TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>(-2)), T(-2) );
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>(-1.3)), T(-1) );
   TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>(-1.5)), T(-1) );
   TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>(-1.6)), T(-1) );
   TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>( 1.3)), T( 1) );
   TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>( 1.5)), T( 1) );
   TTS_EQUAL(eve::tolerant(eve::trunc)(static_cast<T>( 1.6)), T( 1) );

   using eve::as;

   TTS_EQUAL(eve::tolerant(eve::trunc)(T(1)), T(1));
   TTS_EQUAL(eve::tolerant(eve::trunc)(eve::oneminus(eve::eps(as<T>()))), T(1));
   TTS_EQUAL(eve::tolerant(eve::trunc)(eve::oneminus(2*eve::eps(as<T>()))), T(1));
   TTS_EQUAL(eve::tolerant(eve::trunc)(eve::oneminus(3*eve::eps(as<T>()))), T(1));
   TTS_EQUAL(eve::tolerant(eve::trunc)(eve::oneminus(4*eve::eps(as<T>()))), T(0));
//    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::prev(T(45))), T(45));
//    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::prev(T(45), 2)), T(45));
//    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::prev(T(45), 3)), T(45));
//    TTS_EQUAL(eve::tolerant(eve::trunc)(eve::prev(T(45), 4)), T(44));
  }
}
