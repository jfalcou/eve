//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::eps(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eps behavior")
{
  using eve::eps; 
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL((eps(eve::Inf<EVE_TYPE>())), (eve::Nan<EVE_TYPE>()));
      TTS_IEEE_EQUAL((eps(eve::Minf<EVE_TYPE>())), (eve::Nan<EVE_TYPE>()));
      TTS_IEEE_EQUAL((eps(eve::Nan<EVE_TYPE>())), (eve::Nan<EVE_TYPE>()));
    }
    TTS_EQUAL((eps(eve::Mone<EVE_TYPE>())), (eve::Eps<EVE_TYPE>()));
    TTS_EQUAL((eps(eve::One<EVE_TYPE>())) , (eve::Eps<EVE_TYPE>()));
    
    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL((eps(EVE_TYPE{0})), (eve::Mindenormal<EVE_TYPE>()));
    }
  } 
  else
  {
    TTS_EQUAL((eps(eve::Mone<EVE_TYPE>())), (eve::One<EVE_TYPE>()));
    TTS_EQUAL((eps(eve::One<EVE_TYPE>())), (eve::One<EVE_TYPE>()));
    TTS_EQUAL((eps(eve::Zero<EVE_TYPE>())),(eve::One<EVE_TYPE>()));
  } 
}
