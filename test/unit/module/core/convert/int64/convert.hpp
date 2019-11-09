//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::convert return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int64_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int64_t;
#endif

  TTS_EXPR_IS(eve::convert(Type(), eve::as<std::int64_t>()), target_t);
  TTS_EXPR_IS(eve::convert(Type(), eve::int64_)     , target_t);
}

TTS_CASE("Check eve::convert behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int64_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int64_t;
#endif
//   std::cout << "1========================================================================== " << Cardinal << std::endl;
//   auto a = eve::convert(eve::Valmax<Type>(), eve::int64_);
//   std::cout << "Vmax" << eve::Valmax<Type>() << std::endl; 
//   std::cout << "a " << a << std::endl;
//   std::cout << "2========================================================================== " << std::endl; 
//   auto b = static_cast<target_t>(eve::Valmax<Value>()); 
//   std::cout << "b " << b << std::endl;
//   std::cout << "3========================================================================== " << std::endl;
//   TTS_EQUAL(a, b); 
//   std::cout << "4========================================================================== " << std::endl; 

  TTS_EQUAL(eve::convert(eve::Valmin<Type>(), eve::int64_), static_cast<target_t>(eve::Valmin<Value>()) );
  TTS_EQUAL(eve::convert((Type(0))          , eve::int64_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((Type(42.69))      , eve::int64_), static_cast<target_t>(Value(42.69)) );
  if constexpr(std::is_integral_v<Value>)
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::convert(eve::Valmax<Type>(), eve::int64_), static_cast<target_t>(eve::Valmax<Value>()) );    
  }
}
