//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IFREXP_HPP
#define IFREXP_HPP

#include <eve/function/ifrexp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/platform.hpp>
#include <tuple>

TTS_CASE("Check eve::ifrexp behavior")
{

  TTS_EXPR_IS ( (eve::raw_(eve::ifrexp)(Type(0)))
              , (std::tuple<Type,eve::detail::as_integer_t<Type,signed>>)
              );
  
  auto [m, e] = eve::raw_(eve::ifrexp)(Type(1));
  TTS_EQUAL(m  , Type(0.5));
  TTS_EQUAL(e , Type(1));
//   [m, e] = eve::raw_(eve::ifrexp)(eve::Valmax<TTS_EXPR_IS>());
//   TTS_ULP_EQUAL (m , Type(1)-eve::Eps<Type1>()/2, 1);
//   TTS_EQUAL(e , eve::Limitexponent<Type>());
//   TTS_EQUAL(eve::ldexp(m, e),eve::Valmax<Type>());
}


// TS_CASE("Check eve::ifrexp behavior")
// {
//   TTS_EQUAL(eve::ifrexp(Type{0}, Type{0}), Type{0});
//   TTS_EQUAL(eve::ifrexp(Type{0}, Type{1}), Type{0});
//   TTS_EQUAL(eve::ifrexp(Type{1}, Type{0}), Type{1});
//   TTS_EQUAL(eve::ifrexp(Type{1}, Type{1}), Type{2});
//   TTS_EQUAL(eve::ifrexp(Type{1}, Type{2}), Type{4});
//   TTS_EQUAL(eve::ifrexp(Type{3}, Type{4}), Type{48});
//   if constexpr(std::is_floating_point_v<Type>)
//   {
//     TTS_EQUAL(eve::ifrexp(-Type{0}, Type{1}), Type{0});
//     TTS_EXPECT(eve::is_negative(eve::ifrexp(-Type{0}, Type{1})));
//     TTS_EXPECT(eve::is_positive(eve::ifrexp(Type{0}, Type{1})));
//     if constexpr(eve::platform::supports_infinites)
//     {
//       TTS_EQUAL(eve::ifrexp(eve::Minf<Type>(), Type{1}), eve::Minf<Type>());
//       TTS_EQUAL(eve::ifrexp(eve::Inf<Type>(), Type{1}), eve::Inf<Type>());
//     }
//     if constexpr(eve::platform::supports_invalids)
//     {
//       TTS_IEEE_EQUAL(eve::ifrexp(eve::Nan<Type>(), Type{1}), eve::Nan<Type>());
//     }
//     if constexpr(eve::platform::supports_denormals)
//     {
//       TTS_EQUAL(eve::ifrexp(Type{3}, Type{4.3}), Type{48});
//       TTS_EQUAL(eve::ifrexp(eve::Smallestposval<Type>()/2,  Type{1}), eve::Smallestposval<Type>());
//       TTS_EQUAL(eve::ifrexp(eve::Smallestposval<Type>(), Type{-1}), eve::Smallestposval<Type>()/2); 
//       TTS_EQUAL(eve::ifrexp(eve::Mindenormal<Type>(), Type{1}), eve::Mindenormal<Type>()*2);
//       TTS_EQUAL(eve::ifrexp(eve::Mindenormal<Type>(), Type{-1}), eve::Mindenormal<Type>()/2);
//     }
//   }
// }

// TTS_CASE("Check pedantic_(eve::ifrexp) behavior")
// {
//   TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type{0}, 0), Type{0});
//   TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type{0}, 1), Type{0});
//   TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type{1}, 0), Type{1});
//   TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type{1}, 1), Type{2});
//   TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type{1}, 2), Type{4});
//   TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type{3}, 4), Type{48});
//   if constexpr(std::is_floating_point_v<Type>)
//   {
//     TTS_EQUAL(eve::pedantic_(eve::ifrexp)(-Type{0}, 1), Type{0});
//     TTS_EXPECT(eve::is_negative(eve::pedantic_(eve::ifrexp)(-Type{0}, 1)));
//     TTS_EXPECT(eve::is_positive(eve::pedantic_(eve::ifrexp)(Type{0}, 1)));     
//     TTS_EQUAL(eve::ifrexp(Type(1.5), eve::Minexponent<Type>()-1), Type{0});
//     if constexpr(eve::platform::supports_infinites)
//     { 
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Minf<Type>(), 1), eve::Minf<Type>());
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Inf<Type>(),  1), eve::Inf<Type>());
//     }
//     if constexpr(eve::platform::supports_invalids)
//     {
//       TTS_IEEE_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Nan<Type>(),  1), eve::Nan<Type>());
//     }
//     if constexpr(eve::platform::supports_denormals)
//     {
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Smallestposval<Type>()/2,  1), eve::Smallestposval<Type>());
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Smallestposval<Type>()/2, -1), eve::Smallestposval<Type>()/4);
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Mindenormal<Type>(), 1), eve::Mindenormal<Type>()*2);
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(eve::Mindenormal<Type>(), -1), eve::Mindenormal<Type>()/2);
//     }    
//     for(int i=eve::Minexponent<Type>()-10; i < eve::Minexponent<Type>(); ++i)
//     {
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type(1.5), i), Type(std::ifrexp(Type(1.5), i)));
//       TTS_EQUAL(eve::pedantic_(eve::ifrexp)(Type(-1.5), i),Type(std::ifrexp(Type(-1.5), i)));
//     }
//   }
// }

#endif
