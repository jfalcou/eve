//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/extract.hpp>
#include <eve/function/any.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/prev.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check eve::pedantic_(eve::rsqrt) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::rsqrt)(Type(0)), (Type));
}

TTS_CASE("Check eve::pedantic_(eve::rsqrt) behavior")
{
  TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(Type(1)), (Type(1  )), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(Type(4)), (Type(0.5)), 0.5);
  if constexpr(std::is_floating_point_v<Value> && eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL((eve::pedantic_(eve::rsqrt)(eve::Nan<Type>())) , (eve::Nan<Type>()));
    TTS_EQUAL(eve::pedantic_(eve::rsqrt)((Type(0)))               , eve::Inf<Type>());
  }
  for(auto z = eve::Mindenormal<Value>(); z < eve::Valmax<Value>() ; z*= 10 )
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(Type(z)), Type(eve::rec(std::sqrt(z))), 2.0);
//    auto d = eve::ulpdist(eve::pedantic_(eve::rsqrt)(Type(z)), Type(eve::rec(std::sqrt(z)))); 
//     std::cout << z << " -> " << d << std::endl;
//     if ( eve::any(d >=  2.0))
//     {
//       std::cout <<" * " << z << " -> " << eve::pedantic_(eve::rsqrt)(Type(z)) << "  " << Type(eve::rec(std::sqrt(z))) << "  " << d << std::endl;
//       break;
//     }
  }
}

