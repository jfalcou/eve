//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SINCOSH_HPP
#define SINCOSH_HPP

#include <eve/function/sincosh.hpp>
#include <eve/function/ldexp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/platform.hpp>
#include <eve/detail/meta.hpp>
#include <tuple>
#include <cstdlib>


TTS_CASE("Check eve::sincosh behavior")
{
  TTS_EXPR_IS ( (eve::sincosh(Type(0)))
              , (std::pair<Type,Type>)
              );
  {
    auto [m, e ] = eve::sincosh(eve::Zero<Type>());
    TTS_EQUAL(m  , Type(0); );
    TTS_EQUAL(e ,  Type(1););
  }
  
  for(Type i=1; i <Maxlog<Type>() ; i*= 3)
  {
    Type m, e; 
    std::tie(m, e) = eve::sincosh(i);
    TTS_EQUAL(m  , eve::cosh(i));
    TTS_EQUAL(e , eve::sinh(i));
  }
  
}



#endif
