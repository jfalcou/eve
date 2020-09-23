//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>

TTS_CASE_TPL("Check eve::toward_zero(eve::rem) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::toward_zero(eve::rem)(T()  , T()  ), T);
  TTS_EXPR_IS(eve::toward_zero(eve::rem)(T()  , v_t()), T);
  TTS_EXPR_IS(eve::toward_zero(eve::rem)(v_t(), T()  ), T);
}

TTS_CASE_TPL("Check eve::toward_zero(eve::rem) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::integral_value<T> && eve::signed_value<T>)
  {
    TTS_EQUAL(eve::toward_zero(eve::rem)(  T(-1),   T(2)), T(-1));
    TTS_EQUAL(eve::toward_zero(eve::rem)(v_t(-1),   T(2)), T(-1));
    TTS_EQUAL(eve::toward_zero(eve::rem)(  T(-1), v_t(2)), T(-1));
    TTS_EQUAL(eve::toward_zero(eve::rem)(  T(-4),   T(3)), T(-1));
    TTS_EQUAL(eve::toward_zero(eve::rem)(v_t(-4),   T(3)), T(-1));
    TTS_EQUAL(eve::toward_zero(eve::rem)(  T(-4), v_t(3)), T(-1));
  }

  TTS_EQUAL(eve::toward_zero(eve::rem)(T{12}, T(4)), T(0));
  TTS_EQUAL(eve::toward_zero(eve::rem)(T( 1), T(2)), T(1));
  TTS_EQUAL(eve::toward_zero(eve::rem)(T( 4), T(3)), T(1));

  TTS_EQUAL(eve::toward_zero(eve::rem)(v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::toward_zero(eve::rem)(v_t( 1), T(2)), T(1));
  TTS_EQUAL(eve::toward_zero(eve::rem)(v_t( 4), T(3)), T(1));

  TTS_EQUAL(eve::toward_zero(eve::rem)(T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::toward_zero(eve::rem)(T( 1), v_t(2)), T(1));
  TTS_EQUAL(eve::toward_zero(eve::rem)(T( 4), v_t(3)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::toward_zero(eve::rem)(  T(0),   T(1)), T(0));
    TTS_EQUAL(eve::toward_zero(eve::rem)(  T(-0),   T(1)), T(0));
    TTS_EXPECT(eve::all(eve::is_negative(eve::toward_zero(eve::rem)(  -T(0), T(1)))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::toward_zero(eve::rem)(  T(0) , T(1)))));
    TTS_IEEE_EQUAL(eve::toward_zero(eve::rem)(  T(1),   T(0)), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::toward_zero(eve::rem)(  T(-1),   T(0)), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::toward_zero(eve::rem)(  eve::inf(eve::as<T>()),   T(0)), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::toward_zero(eve::rem)(  eve::minf(eve::as<T>()),   T(0)), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::toward_zero(eve::rem)( T(1),  eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::toward_zero(eve::rem)( T(1), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }
}
