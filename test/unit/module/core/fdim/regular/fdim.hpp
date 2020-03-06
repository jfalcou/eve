//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fdim.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::fdim return type")
{
  TTS_EXPR_IS(eve::fdim(Type(), Type()), (Type));
}

TTS_CASE(" fdim behaviour")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::fdim(eve::Inf<Type>(), eve::Inf<Type>()), eve::Zero<Type>());
    TTS_EQUAL(eve::fdim(eve::Minf<Type>(), eve::Minf<Type>()), eve::Zero<Type>());
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<Type>(), eve::Nan<Type>())), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<Type>(), eve::Zero<Type>())), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Zero<Type>(), eve::Nan<Type>())), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<Type>(), eve::Zero<Type>())), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::One<Type>(), eve::Nan<Type>())), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL((eve::fdim(eve::Nan<Type>(), eve::One<Type>())), eve::Nan<Type>(), 0);
  }
  TTS_EQUAL((eve::fdim(eve::Mone<Type>(), eve::Mone<Type>())), eve::Zero<Type>());
  TTS_EQUAL((eve::fdim(eve::One<Type>(), eve::One<Type>())), eve::Zero<Type>());
  TTS_EQUAL((eve::fdim(eve::Zero<Type>(), eve::Zero<Type>())), eve::Zero<Type>());
  TTS_EQUAL((eve::fdim(eve::One<Type>(), eve::Zero<Type>())), eve::One<Type>());
  TTS_EQUAL((eve::fdim(Type(2), Type(-3))), Type(5));
  TTS_EQUAL((eve::fdim(Type(2), Type(3))), Type(0));
}
