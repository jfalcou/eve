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
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE_TPL("Check nextafter return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::nextafter(T(), T())), T);
  TTS_EXPR_IS((eve::nextafter(T(), v_t())), T);
  TTS_EXPR_IS((eve::nextafter(v_t(), T())), T);
}

TTS_CASE_TPL("Check eve::nextafter one parameter behavior", EVE_TYPE)
{
  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL((eve::nextafter(T{1}, T{1})), T(1));
    TTS_EQUAL((eve::nextafter(T{1}, T{5})), T(2));
    TTS_EQUAL((eve::nextafter(T{2}, T(0))), T(1));
    TTS_EQUAL((eve::nextafter(v_t{1}, T{1})), T(1));
    TTS_EQUAL((eve::nextafter(v_t{1}, T{5})), T(2));
    TTS_EQUAL((eve::nextafter(v_t{2}, T(0))), T(1));
    TTS_EQUAL((eve::nextafter(T{1}, v_t{1})), T(1));
    TTS_EQUAL((eve::nextafter(T{1}, v_t{5})), T(2));
    TTS_EQUAL((eve::nextafter(T{2}, v_t(0))), T(1));

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL((eve::nextafter(T(-1), T(-1))), T(-1));
      TTS_EQUAL((eve::nextafter(T(-1), T(5))), T(0));
      TTS_EQUAL((eve::nextafter(v_t(-2), T(-4))), T(-3));
      TTS_EQUAL((eve::nextafter(v_t(-1), T(-1))), T(-1));
      TTS_EQUAL((eve::nextafter(v_t(-1), T(5))), T(0));
      TTS_EQUAL((eve::nextafter(v_t(-2), T(-4))), T(-3));
      TTS_EQUAL((eve::nextafter(T(-1), v_t(-1))), T(-1));
      TTS_EQUAL((eve::nextafter(T(-1), v_t(5))), T(0));
      TTS_EQUAL((eve::nextafter(T(-2), v_t(-4))), T(-3));
    }

  }
  else
  {
    TTS_EQUAL((eve::nextafter(eve::Mone<T>(), T(2)))        , (eve::Mone<T>()+eve::Eps<T>()/2));
    TTS_EQUAL((eve::nextafter(eve::One<T>(), T(-1)))        , (eve::One<T>()-eve::Eps<T>()/2));
    TTS_EQUAL((eve::nextafter(eve::One<T>(), T(1)))        , (eve::One<T>()));
    TTS_EQUAL((eve::nextafter(eve::Mone<v_t>(), T(2)))       , (eve::Mone<T>()+eve::Eps<T>()/2));
    TTS_EQUAL((eve::nextafter(eve::One<v_t>(), T(-1)))       , (eve::One<T>()-eve::Eps<T>()/2));
    TTS_EQUAL((eve::nextafter(eve::One<v_t>(), T(1)))       , (eve::One<T>()));
    TTS_EQUAL((eve::nextafter(eve::Mone<T>(), v_t(2)))       , (eve::Mone<T>()+eve::Eps<T>()/2));
    TTS_EQUAL((eve::nextafter(eve::One<T>(), v_t(-1)))       , (eve::One<T>()-eve::Eps<T>()/2));
    TTS_EQUAL((eve::nextafter(eve::One<v_t>(), T(1)))       , (eve::One<T>()));
  }
}
