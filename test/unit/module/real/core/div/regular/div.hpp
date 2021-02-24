//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check eve::div return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::div(T()  , T()   ), T);
  TTS_EXPR_IS(eve::div(T()  , v_t() ), T);
  TTS_EXPR_IS(eve::div(v_t(), T()   ), T);
}

TTS_CASE_TPL("Check eve::div behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::div(T( 0), T(1)), (T(0  )));
  TTS_EQUAL(eve::div(T( 1), T(1)), (T(1  )));
  TTS_EQUAL(eve::div(T(12), T(4)), (T(3  )));
  TTS_EQUAL(eve::div(T( 1), T(2)), (T(0.5)));

  TTS_EQUAL(eve::div(v_t( 0), T(1)), (T(0  )));
  TTS_EQUAL(eve::div(v_t( 1), T(1)), (T(1  )));
  TTS_EQUAL(eve::div(v_t(12), T(4)), (T(3  )));
  TTS_EQUAL(eve::div(v_t( 1), T(2)), (T(0.5)));

  TTS_EQUAL(eve::div(T( 0), v_t(1)), (T(0  )));
  TTS_EQUAL(eve::div(T( 1), v_t(1)), (T(1  )));
  TTS_EQUAL(eve::div(T(12), v_t(4)), (T(3  )));
  TTS_EQUAL(eve::div(T( 1), v_t(2)), (T(0.5)));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::div(eve::valmax(eve::as<T>())   ,   T(2)) , T(eve::valmax(eve::as<v_t>())/2));
    TTS_EQUAL(eve::div(eve::valmax(eve::as<v_t>()) ,   T(2)) , T(eve::valmax(eve::as<v_t>())/2));
    TTS_EQUAL(eve::div(eve::valmax(eve::as<T>())   , v_t(2)) , T(eve::valmax(eve::as<v_t>())/2));

    TTS_EQUAL(eve::div(eve::valmax(eve::as<T>())   ,   T(1)) , eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::div(eve::valmax(eve::as<v_t>()) ,   T(1)) , eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::div(eve::valmax(eve::as<T>())   , v_t(1)) , eve::valmax(eve::as<T>()));
  }

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::div(T(-1), T( 1)), T(-1) );
    TTS_EQUAL(eve::div(T(-6), T(-2)), T( 3) );

    TTS_EQUAL(eve::div(v_t(-1), T( 1)), T(-1) );
    TTS_EQUAL(eve::div(v_t(-6), T(-2)), T( 3) );

    TTS_EQUAL(eve::div(T(-1), v_t( 1)), T(-1) );
    TTS_EQUAL(eve::div(T(-6), v_t(-2)), T( 3) );
  }
}
