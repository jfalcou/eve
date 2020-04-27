//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minmag.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::minmag return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::minmag(T(0)  , T(0) ) , T);
  TTS_EXPR_IS(eve::minmag(v_t(0) , T(0) ) , T);
  TTS_EXPR_IS(eve::minmag(T(0)  , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::minmag behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::minmag((T(0)), (T(0))), (T(0)));
  TTS_EQUAL(eve::minmag((T(0)), (T(1))), (T(0)));
  TTS_EQUAL(eve::minmag((T(1)), (T(0))), (T(0)));
  TTS_EQUAL(eve::minmag((T(1)), (T(1))), (T(1)));

  TTS_EQUAL(eve::minmag((v_t(0)), (T(0))), (T(0)));
  TTS_EQUAL(eve::minmag((v_t(0)), (T(1))), (T(0)));
  TTS_EQUAL(eve::minmag((v_t(1)), (T(0))), (T(0)));
  TTS_EQUAL(eve::minmag((v_t(1)), (T(1))), (T(1)));

  TTS_EQUAL(eve::minmag((T(0)), (v_t(0))), (T(0)));
  TTS_EQUAL(eve::minmag((T(0)), (v_t(1))), (T(0)));
  TTS_EQUAL(eve::minmag((T(1)), (v_t(0))), (T(0)));
  TTS_EQUAL(eve::minmag((T(1)), (v_t(1))), (T(1)));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::minmag(static_cast<T>(-3), (T(2))), (T(2)));
    TTS_EQUAL(eve::minmag(static_cast<T>(-1), (T(2))), static_cast<T>(-1));
    TTS_EQUAL(eve::minmag(static_cast<T>(-2), (T(2))), static_cast<T>(-2));

    TTS_EQUAL(eve::minmag(static_cast<T>(-3), (T(2))), (T(2)));
    TTS_EQUAL(eve::minmag(static_cast<T>(-1), (T(2))), static_cast<T>(-1));
    TTS_EQUAL(eve::minmag(static_cast<T>(-2), (T(2))), static_cast<T>(-2));

    TTS_EQUAL(eve::minmag(static_cast<T>(-3), (T(2))), (T(2)));
    TTS_EQUAL(eve::minmag(static_cast<T>(-1), (T(2))), static_cast<T>(-1));
    TTS_EQUAL(eve::minmag(static_cast<T>(-2), (T(2))), static_cast<T>(-2));
  }
}
