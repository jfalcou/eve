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
#include <eve/constant/nan.hpp>


TTS_CASE_TPL("Check nextafter return type", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::pedantic(eve::nextafter)(  T(),  T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::nextafter)(  T(),v_t()), T);
  TTS_EXPR_IS(eve::pedantic(eve::nextafter)(v_t(),  T()), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::nextafter) one parameter behavior", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::pedantic(eve::nextafter)(T(1)  ,   T(1)), T(1));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(T(1)  ,   T(5)), T(2));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(T(2)  ,   T(0)), T(1));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t(1),   T(1)), T(1));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t(1),   T(5)), T(2));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t(2),   T(0)), T(1));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(T(1)  , v_t(1)), T(1));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(T(1)  , v_t(5)), T(2));
    TTS_EQUAL(eve::pedantic(eve::nextafter)(T(2)  , v_t(0)), T(1));

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::pedantic(eve::nextafter)(   T(-1),   T(-1)), T(-1));
      TTS_EQUAL(eve::pedantic(eve::nextafter)(   T(-1),   T( 5)), T( 0));
      TTS_EQUAL(eve::pedantic(eve::nextafter)( v_t(-2),   T(-4)), T(-3));
      TTS_EQUAL(eve::pedantic(eve::nextafter)( v_t(-1),   T(-1)), T(-1));
      TTS_EQUAL(eve::pedantic(eve::nextafter)( v_t(-1),   T( 5)), T( 0));
      TTS_EQUAL(eve::pedantic(eve::nextafter)( v_t(-2),   T(-4)), T(-3));
      TTS_EQUAL(eve::pedantic(eve::nextafter)(   T(-1), v_t(-1)), T(-1));
      TTS_EQUAL(eve::pedantic(eve::nextafter)(   T(-1), v_t( 5)), T( 0));
      TTS_EQUAL(eve::pedantic(eve::nextafter)(   T(-2), v_t(-4)), T(-3));
    }
  }
  else
  {
    using eve::as;
    TTS_EQUAL(eve::pedantic(eve::nextafter)(  T(-1),   T( 2)), T(-1)+eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(  T( 1),   T(-1)), T( 1)-eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(  T( 1),   T( 1)), T( 1)                 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t(-1),   T( 2)), T(-1)+eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t( 1),   T(-1)), T( 1)-eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t( 1),   T( 1)), T( 1)                 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(  T(-1), v_t( 2)), T(-1)+eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(  T( 1), v_t(-1)), T( 1)-eve::eps(as<T>())/2 );
    TTS_EQUAL(eve::pedantic(eve::nextafter)(v_t( 1),   T( 1)), T( 1)                 );

    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(eve::nan(eve::as<T>())  , T(1)           ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(T(1)           , eve::nan(eve::as<T>())  ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(eve::nan(eve::as<v_t>()), T(1)           ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(v_t(1)         , eve::nan(eve::as<T>())  ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(eve::nan(eve::as<T>())  , v_t(1)         ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(T(1)           , eve::nan(eve::as<v_t>())), eve::nan(eve::as<T>()));
  }
}
