//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/eps.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check eve::eps return type")
{
  TTS_EXPR_IS(eve::eps(Type(0)), (Type));
}

TTS_CASE("Check eve::eps behavior")
{
  using eve::eps; 
  if constexpr(std::is_floating_point_v<Value>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL((eps(eve::Inf<Type>())), (eve::Nan<Type>()));
      TTS_IEEE_EQUAL((eps(eve::Minf<Type>())), (eve::Nan<Type>()));
      TTS_IEEE_EQUAL((eps(eve::Nan<Type>())), (eve::Nan<Type>()));
    }
    TTS_EQUAL((eps(eve::Mone<Type>())), (eve::Eps<Type>()));
    TTS_EQUAL((eps(eve::One<Type>())) , (eve::Eps<Type>()));
    
    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL((eps(Type{0})), (eve::Mindenormal<Type>()));
    }
  } 
  else
  {
    TTS_EQUAL((eps(eve::Mone<Type>())), (eve::One<Type>()));
    TTS_EQUAL((eps(eve::One<Type>())), (eve::One<Type>()));
    TTS_EQUAL((eps(eve::Zero<Type>())),(eve::One<Type>()));
  } 
}
