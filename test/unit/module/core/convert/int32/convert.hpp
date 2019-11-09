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
#include <eve/function/any.hpp>
#include <eve/function/sub.hpp>
#include <type_traits>

TTS_CASE("Check eve::convert return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int32_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int32_t;
#endif

  TTS_EXPR_IS(eve::convert(Type(), eve::as<std::int32_t>()), target_t);
  TTS_EXPR_IS(eve::convert(Type(), eve::int32_)     , target_t);
}

TTS_CASE("Check eve::convert behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int32_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int32_t;
#endif

  TTS_EQUAL(eve::convert(eve::Valmin<Type>(), eve::int32_), static_cast<target_t>(eve::Valmin<Value>()) );
  TTS_EQUAL(eve::convert((Type(0))          , eve::int32_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((Type(42.69))      , eve::int32_), static_cast<target_t>(Value(42.69)) );
  if constexpr(std::is_integral_v<Value>)
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::convert(eve::Valmax<Type>(), eve::int32_), static_cast<target_t>(eve::Valmax<Value>()));
  }
  
// TTS_EXPECT_NOT(eve::any(eve::convert(eve::Valmax<Type>(), eve::int32_)- static_cast<target_t>(eve::Valmax<Value>())));

//   std::cout << "1========================================================================== " << Cardinal << std::endl;
//   auto a = eve::convert(eve::Valmax<Type>(), eve::int32_);
//   std::cout << "Vmax" << eve::Valmax<Type>() << std::endl; 
//   std::cout << "a " << a << std::endl;
//   std::cout << "2========================================================================== " << std::endl; 
//   auto b = static_cast<target_t>(eve::Valmax<Value>()); 
//   std::cout << "b " << b << std::endl;
//   std::cout << "3========================================================================== " << std::endl;
//   TTS_EQUAL(a, b); 
//   std::cout << "4========================================================================== " << std::endl; 

//   auto vvm =  eve::Valmax<Value>();
//   auto vcvm = static_cast<target_t>(vvm);
//   auto tvm =   eve::Valmax<Type>();
//   auto tcvm =  eve::convert(tvm,eve::int32_); //eve::as_<std::int32_t>());
//   auto ref  =  static_cast<target_t>(eve::Valmax<Value>());
//   std::cout << "Cardinal                         " << Cardinal << std::endl; 
//   std::cout << "vvm = eve::Valmax<Value>()       " << vvm << std::endl;
//   std::cout << "static_cast<target_t>(vvm)       " << vcvm << std::endl;
//   std::cout << "tvm = eve::Valmax<Type>()        " << tvm << std::endl;
//   std::cout << "eve::convert(tvm,eve::int32_)    " << tcvm << std::endl;
//   std::cout << "ref = static_cast<target_t>(vvm) " << ref  << std::endl;     
//    TTS_EQUAL(tcvm, ref); 
}
