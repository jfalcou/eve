//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ULP_HPP
#define ULP_HPP

#include <eve/function/scalar/ulp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check ulp return type")
{
  TTS_EXPR_IS(eve::ulp(Type()), Type);
}

TTS_CASE("Check eve::ulp behavior")
{
  using eve::ulp; 
  if constexpr(std::is_floating_point_v<Type>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(ulp(eve::Inf<Type>()), eve::Nan<Type>());
      TTS_IEEE_EQUAL(ulp(eve::Minf<Type>()), eve::Nan<Type>());
      TTS_IEEE_EQUAL(ulp(eve::Nan<Type>()), eve::Nan<Type>());
    }
    TTS_EQUAL(ulp(eve::Mone<Type>()), eve::Eps<Type>()/2);
    TTS_EQUAL(ulp(eve::One<Type>()), eve::Eps<Type>()/2);
    TTS_EQUAL(ulp(eve::Zero<Type>()), eve::Mindenormal<Type>());
  } 
  else
  {
    TTS_EQUAL(ulp(eve::Mone<Type>()), eve::One<Type>());
    TTS_EQUAL(ulp(eve::One<Type>()), eve::One<Type>());
    TTS_EQUAL(ulp(eve::Zero<Type>()), eve::One<Type>());
  }
}

#endif
