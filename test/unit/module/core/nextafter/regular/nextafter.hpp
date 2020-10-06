//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nextafter.hpp>
#include <eve/constant/eps.hpp>

TTS_CASE("Check nextafter return type")
{
  TTS_EXPR_IS(eve::nextafter( EVE_TYPE()  , EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::nextafter( EVE_TYPE()  , EVE_VALUE() ), EVE_TYPE);
  TTS_EXPR_IS(eve::nextafter( EVE_VALUE() , EVE_TYPE()  ), EVE_TYPE);
}

TTS_CASE_TPL("Check eve::nextafter one parameter behavior", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::nextafter(T(1)  ,   T(1)), T(1));
    TTS_EQUAL(eve::nextafter(T(1)  ,   T(5)), T(2));
    TTS_EQUAL(eve::nextafter(T(2)  ,   T(0)), T(1));
    TTS_EQUAL(eve::nextafter(v_t(1),   T(1)), T(1));
    TTS_EQUAL(eve::nextafter(v_t(1),   T(5)), T(2));
    TTS_EQUAL(eve::nextafter(v_t(2),   T(0)), T(1));
    TTS_EQUAL(eve::nextafter(T(1)  , v_t(1)), T(1));
    TTS_EQUAL(eve::nextafter(T(1)  , v_t(5)), T(2));
    TTS_EQUAL(eve::nextafter(T(2)  , v_t(0)), T(1));

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::nextafter(   T(-1),   T(-1)), T(-1));
      TTS_EQUAL(eve::nextafter(   T(-1),   T( 5)), T( 0));
      TTS_EQUAL(eve::nextafter( v_t(-2),   T(-4)), T(-3));
      TTS_EQUAL(eve::nextafter( v_t(-1),   T(-1)), T(-1));
      TTS_EQUAL(eve::nextafter( v_t(-1),   T( 5)), T( 0));
      TTS_EQUAL(eve::nextafter( v_t(-2),   T(-4)), T(-3));
      TTS_EQUAL(eve::nextafter(   T(-1), v_t(-1)), T(-1));
      TTS_EQUAL(eve::nextafter(   T(-1), v_t( 5)), T( 0));
      TTS_EQUAL(eve::nextafter(   T(-2), v_t(-4)), T(-3));
    }
  }
  else
  {
    using eve::as;
    TTS_EQUAL(eve::nextafter(  T(-1),   T( 2)), T(-1)+eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::nextafter(  T( 1),   T(-1)), T( 1)-eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::nextafter(  T( 1),   T( 1)), T( 1)                 );
    TTS_EQUAL(eve::nextafter(v_t(-1),   T( 2)), T(-1)+eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::nextafter(v_t( 1),   T(-1)), T( 1)-eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::nextafter(v_t( 1),   T( 1)), T( 1)                 );
    TTS_EQUAL(eve::nextafter(  T(-1), v_t( 2)), T(-1)+eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::nextafter(  T( 1), v_t(-1)), T( 1)-eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::nextafter(v_t( 1),   T( 1)), T( 1)                 );
  }
}
