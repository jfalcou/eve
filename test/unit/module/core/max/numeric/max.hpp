//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <eve/function/numeric.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::numeric_(eve::max) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::numeric_(eve::max)(T(0)  , T(0) ) , T);
  TTS_EXPR_IS(eve::numeric_(eve::max)(v_t(0) , T(0) ) , T);
  TTS_EXPR_IS(eve::numeric_(eve::max)(T(0)  , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::numeric_(eve::max) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::numeric_(eve::max)((T(0)), (T(0))), (T(0)));
  TTS_EQUAL(eve::numeric_(eve::max)((T(0)), (T(1))), (T(1)));
  TTS_EQUAL(eve::numeric_(eve::max)((T(1)), (T(0))), (T(1)));
  TTS_EQUAL(eve::numeric_(eve::max)((T(1)), (T(1))), (T(1)));

  TTS_EQUAL(eve::numeric_(eve::max)((v_t(0)), (T(0))), (T(0)));
  TTS_EQUAL(eve::numeric_(eve::max)((v_t(0)), (T(1))), (T(1)));
  TTS_EQUAL(eve::numeric_(eve::max)((v_t(1)), (T(0))), (T(1)));
  TTS_EQUAL(eve::numeric_(eve::max)((v_t(1)), (T(1))), (T(1)));

  TTS_EQUAL(eve::numeric_(eve::max)((T(0)), (v_t(0))), (T(0)));
  TTS_EQUAL(eve::numeric_(eve::max)((T(0)), (v_t(1))), (T(1)));
  TTS_EQUAL(eve::numeric_(eve::max)((T(1)), (v_t(0))), (T(1)));
  TTS_EQUAL(eve::numeric_(eve::max)((T(1)), (v_t(1))), (T(1)));

  if constexpr(eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::numeric_(eve::max)((eve::Nan<T>() ), (T(1)))  , (T(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::max)((eve::Nan<v_t>()), (T(1)))  , (T(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::max)((eve::Nan<T>() ), (v_t(1))) , (T(1)) );

    TTS_IEEE_EQUAL(eve::numeric_(eve::max)((T(1))  , (eve::Nan<T>())  ), (T(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::max)((v_t(1)) , (eve::Nan<T>())  ), (T(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::max)((T(1))  , (eve::Nan<v_t>()) ), (T(1)) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::numeric_(eve::max)(T(-0.), T( 0 )))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::numeric_(eve::max)(T( 0 ), T(-0.)))));
   }
}
