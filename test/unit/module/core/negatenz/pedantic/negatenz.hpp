//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/negatenz.hpp>
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

TTS_CASE("Check eve::pedantic_(eve::negatenz) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::negatenz)(Type(), Type()), (Type));
}

TTS_CASE(" negatenz behaviour")
{
  if constexpr(std::is_floating_point_v<Value>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
      TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Minf<Type>(), eve::Minf<Type>()), eve::Inf<Type>());
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Nan<Type>(), eve::Nan<Type>())), eve::Nan<Type>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Nan<Type>(), eve::Zero<Type>())), eve::Nan<Type>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Zero<Type>(), eve::Nan<Type>())), eve::Nan<Type>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::One<Type>(), eve::Nan<Type>())), eve::Nan<Type>(), 0);
      TTS_ULP_EQUAL((eve::pedantic_(eve::negatenz)(eve::Nan<Type>(), eve::One<Type>())), eve::Nan<Type>(), 0);
    }
    TTS_EQUAL((eve::pedantic_(eve::negatenz)(eve::One<Type>(), eve::Mzero<Type>())), eve::Mone<Type>()); 
    TTS_EQUAL((eve::pedantic_(eve::negatenz)(Type(2), Type(-3))), Type(-2));
    TTS_EQUAL((eve::pedantic_(eve::negatenz)(Type(2), Type(3))), Type(2));
  }
  else if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Mone<Type>(), eve::Mone<Type>()), eve::One<Type>());
    TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Mone<Type>(), eve::One<Type>()), eve::Mone<Type>());
  }
  TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::pedantic_(eve::negatenz)(eve::One<Type>(), eve::Zero<Type>()), eve::One<Type>());
}
