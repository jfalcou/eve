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
#include <eve/function/sinh.hpp>
#include <eve/function/cosh.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
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
    TTS_ULP_EQUAL(m  , Type(0), 0.5);
    TTS_ULP_EQUAL(e ,  Type(1), 0.5);
    TTS_EXPECT(eve::is_positive(m)); 
  }
  {
    auto [m, e ] = eve::sincosh(eve::Mzero<Type>());
    TTS_ULP_EQUAL(m  , Type(0), 0.5);
    TTS_ULP_EQUAL(e ,  Type(1), 0.5);
    TTS_EXPECT(eve::is_negative(m)); 
  }
  {
    auto x = eve::Maxlog<Type>()+eve::Log_2<Type>()/2; 
    auto [m, e ] = eve::sincosh(x);
    TTS_ULP_EQUAL(m  , Type(std::cosh(x)), 0.5);
    TTS_ULP_EQUAL(e ,  Type(std::sinh(x)), 0.5);
  }
  {
    auto x = eve::Inf<Type>(); 
    auto [m, e ] = eve::sincosh(x);
    TTS_ULP_EQUAL(m  , eve::Inf<Type>(), 0.5);
    TTS_ULP_EQUAL(e ,  eve::Inf<Type>(), 0.5);
  }
  
  for(Type i=1; i <eve::Maxlog<Type>() ; i*= 3)
  {
    Type m, e; 
    std::tie(m, e) = eve::sincosh(i);
    TTS_ULP_EQUAL(e  , Type(eve::cosh(i)), 0.5);
    TTS_ULP_EQUAL(m ,  Type(eve::sinh(i)), 0.5);
  }
  
}



#endif
