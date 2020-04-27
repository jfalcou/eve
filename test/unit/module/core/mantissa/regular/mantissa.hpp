//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mantissa.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::mantissa return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::mantissa(T(0))), T);
}

TTS_CASE_TPL("Check eve::mantissa  behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL((eve::mantissa(eve::Inf<T>())), (eve::Inf<T>()));
    TTS_EQUAL((eve::mantissa(eve::Minf<T>())), (eve::Minf<T>()));
    TTS_IEEE_EQUAL((eve::mantissa(eve::Nan<T>())), (eve::Nan<T>()));
  }
  TTS_EQUAL((eve::mantissa(eve::Mone<T>())), (eve::Mone<T>()));
  TTS_EQUAL((eve::mantissa(eve::One<T>())), (eve::One<T>()));
  TTS_EQUAL((eve::mantissa(T( 0 ))), (T( 0 )));
  TTS_EQUAL((eve::mantissa(T(2))), eve::One<T>());
  TTS_EQUAL((eve::mantissa(T(1.5))), T(1.5));
  TTS_EQUAL((eve::mantissa(T(2.5))), T(1.25));
}

