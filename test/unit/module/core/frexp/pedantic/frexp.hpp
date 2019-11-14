//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frexp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>

TTS_CASE("Check frexp return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::frexp)(Type()), (std::tuple<Type,Type>));
}

TTS_CASE("Check eve::pedantic_(eve::frexp) behavior")
{
  {
    auto [p0, p1] = eve::pedantic_(eve::frexp)(Type(1));
    TTS_EQUAL(p0, Type(0.5));
    TTS_EQUAL(p1, Type(1));
  }
  {
    auto [p0, p1] = eve::pedantic_(eve::frexp)(Type(0));
    TTS_EQUAL (p0 , Type(0));
    TTS_EQUAL (p1, Type(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Nan<Type>());
    
    TTS_IEEE_EQUAL(r0 , (eve::Nan<Type>()));
    TTS_EQUAL     (r1, (Type(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Inf<Type>());
    auto [q0, q1] = eve::pedantic_(eve::frexp)(eve::Minf<Type>());
    
    TTS_IEEE_EQUAL(r0, (eve::Inf<Type>()));
    TTS_EQUAL     (r1, Type(0));
    
    TTS_IEEE_EQUAL(q0, (eve::Minf<Type>()));
    TTS_EQUAL     (q1, Type(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Mindenormal<Type>());
    
    TTS_ULP_EQUAL (r0, Type(0.5), 1);
    TTS_EQUAL     (r1, Type(eve::Minexponent<Value>()-eve::Nbmantissabits<Value>()+1));
  }
}
