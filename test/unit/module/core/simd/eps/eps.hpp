//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EPS_HPP
#define EPS_HPP


#include <eve/function/eps.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check eps return type",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t = eve::wide<Type, T>; 
  TTS_EXPR_IS(eve::eps(t_t()), t_t);
}

using eve::fixed;

TTS_CASE_TPL("Check eve::eps behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t = eve::wide<Type, T>; 
  using eve::eps; 
  if constexpr(std::is_floating_point_v<Type>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eps(eve::Inf<t_t>()), eve::Nan<t_t>());
      TTS_IEEE_EQUAL(eps(eve::Minf<t_t>()), eve::Nan<t_t>());
      TTS_IEEE_EQUAL(eps(eve::Nan<t_t>()), eve::Nan<t_t>());
    }
    TTS_EQUAL(eps(t_t{-1}), bs::Eps<t_t>());
    TTS_EQUAL(eps(t_t{1}) , bs::Eps<t_t>());
    
    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL(eps(t_t{0}), bs::Mindenormal<t_t>());
    }
  } 
  else
  {
    TTS_EQUAL(eps(eve::Mone<t_t>()), eve::One<t_t>());
    TTS_EQUAL(eps(eve::One<t_t>()), eve::One<t_t>());
    TTS_EQUAL(eps(eve::Zero<t_t>()), eve::One<t_t>());
  }
} 

#endif
