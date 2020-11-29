//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/numeric/max.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::numeric(eve::max) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::numeric(eve::max)( T(0)  , T(0)   ) , T);
  TTS_EXPR_IS(eve::numeric(eve::max)(v_t(0) , T(0)   ) , T);
  TTS_EXPR_IS(eve::numeric(eve::max)( T(0)  , v_t(0) ) , T);
}

TTS_CASE_TPL("Check eve::numeric(eve::max) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::numeric(eve::max)(T(0), T(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::max)(T(0), T(1)), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(T(1), T(0)), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(T(1), T(1)), T(1));

  TTS_EQUAL(eve::numeric(eve::max)(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::max)(v_t(0), T(1)), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(v_t(1), T(0)), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(v_t(1), T(1)), T(1));

  TTS_EQUAL(eve::numeric(eve::max)(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::numeric(eve::max)(T(0), v_t(1)), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(T(1), v_t(0)), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(T(1), v_t(1)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::numeric(eve::max)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

    TTS_IEEE_EQUAL(eve::numeric(eve::max)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::max)(T(-0.), T( 0 )))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::max)(T( 0 ), T(-0.)))));
   }
}
