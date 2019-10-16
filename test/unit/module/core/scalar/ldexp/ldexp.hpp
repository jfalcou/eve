//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LDEXP_HPP
#define LDEXP_HPP

#include <eve/function/ldexp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::ldexp behavior")
{
  TTS_EQUAL(eve::ldexp(Type{0}, 0), Type{0});
  TTS_EQUAL(eve::ldexp(Type{0}, 1), Type{0});
  TTS_EQUAL(eve::ldexp(Type{1}, 0), Type{1});
  TTS_EQUAL(eve::ldexp(Type{1}, 1), Type{2});
  TTS_EQUAL(eve::ldexp(Type{1}, 2), Type{4});
  TTS_EQUAL(eve::ldexp(Type{3}, 4), Type{48});
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::ldexp(-Type{0}, 1), Type{0});
    TTS_EXPECT(eve::is_negative(eve::ldexp(-Type{0}, 1)));
    TTS_EXPECT(eve::is_positive(eve::ldexp(Type{0}, 1)));     
    TTS_EQUAL(eve::ldexp(Type(1.5), eve::Minexponent<Type>()-1), Type{0});
    
    if constexpr(eve::platform::supports_infinites)
    {
      TTS_EQUAL(eve::ldexp(eve::Minf<Type>(), 1), eve::Minf<Type>());
      TTS_EQUAL(eve::ldexp(eve::Inf<Type>(),  1), eve::Inf<Type>());
    }
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eve::ldexp(eve::Nan<Type>(),  1), eve::Nan<Type>());
    }
    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL(eve::ldexp(eve::Smallestposval<Type>()/2,  1), eve::Smallestposval<Type>());
      TTS_EQUAL(eve::ldexp(eve::Smallestposval<Type>()/2, -1), eve::Smallestposval<Type>()/4);
      TTS_EQUAL(eve::ldexp(eve::Mindenormal<Type>(), 1), eve::Mindenormal<Type>()*2);
      TTS_EQUAL(eve::ldexp(eve::Mindenormal<Type>(), -1), eve::Mindenormal<Type>()/2);
    }    
  }
}

TTS_CASE("Check eve::ldexp behavior")
{
  TTS_EQUAL(eve::ldexp(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::ldexp(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::ldexp(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::ldexp(Type{1}, Type{1}), Type{2});
  TTS_EQUAL(eve::ldexp(Type{1}, Type{2}), Type{4});
  TTS_EQUAL(eve::ldexp(Type{3}, Type{4}), Type{48});
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::ldexp(-Type{0}, Type{1}), Type{0});
    TTS_EXPECT(eve::is_negative(eve::ldexp(-Type{0}, Type{1})));
    TTS_EXPECT(eve::is_positive(eve::ldexp(Type{0}, Type{1})));
    if constexpr(eve::platform::supports_infinites)
    {
      TTS_EQUAL(eve::ldexp(eve::Minf<Type>(), Type{1}), eve::Minf<Type>());
      TTS_EQUAL(eve::ldexp(eve::Inf<Type>(), Type{1}), eve::Inf<Type>());
    }
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eve::ldexp(eve::Nan<Type>(), Type{1}), eve::Nan<Type>());
    }
    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL(eve::ldexp(Type{3}, Type{4}), Type{48});
      TTS_EQUAL(eve::ldexp(eve::Smallestposval<Type>()/2,  Type{1}), eve::Smallestposval<Type>());
      TTS_EQUAL(eve::ldexp(eve::Smallestposval<Type>(), Type{-1}), eve::Smallestposval<Type>()/2); 
      TTS_EQUAL(eve::ldexp(eve::Mindenormal<Type>(), Type{1}), eve::Mindenormal<Type>()*2);
      TTS_EQUAL(eve::ldexp(eve::Mindenormal<Type>(), Type{-1}), eve::Mindenormal<Type>()/2);
    }
  }
}

TTS_CASE("Check pedantic_(eve::ldexp) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type{0}, 0), Type{0});
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type{0}, 1), Type{0});
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type{1}, 0), Type{1});
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type{1}, 1), Type{2});
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type{1}, 2), Type{4});
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type{3}, 4), Type{48});
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::pedantic_(eve::ldexp)(-Type{0}, 1), Type{0});
    TTS_EXPECT(eve::is_negative(eve::pedantic_(eve::ldexp)(-Type{0}, 1)));
    TTS_EXPECT(eve::is_positive(eve::pedantic_(eve::ldexp)(Type{0}, 1)));     
    TTS_EQUAL(eve::ldexp(Type(1.5), eve::Minexponent<Type>()-1), Type{0});
    if constexpr(eve::platform::supports_infinites)
    { 
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Minf<Type>(), 1), eve::Minf<Type>());
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Inf<Type>(),  1), eve::Inf<Type>());
    }
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eve::pedantic_(eve::ldexp)(eve::Nan<Type>(),  1), eve::Nan<Type>());
    }
    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Smallestposval<Type>()/2,  1), eve::Smallestposval<Type>());
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Smallestposval<Type>()/2, -1), eve::Smallestposval<Type>()/4);
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Mindenormal<Type>(), 1), eve::Mindenormal<Type>()*2);
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Mindenormal<Type>(), -1), eve::Mindenormal<Type>()/2);
    }    
    for(int i=eve::Minexponent<Type>()-10; i < eve::Minexponent<Type>(); ++i)
    {
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type(1.5), i), Type(std::ldexp(Type(1.5), i)));
      TTS_EQUAL(eve::pedantic_(eve::ldexp)(Type(-1.5), i),Type(std::ldexp(Type(-1.5), i)));
    }
  }
}

#endif
