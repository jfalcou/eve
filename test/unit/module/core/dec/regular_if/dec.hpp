// //==================================================================================================
// /**
//   EVE - Expressive Vector Engine
//   Copyright 2019 Joel FALCOU
//   Copyright 2019 Jean-Thierry LAPRESTE

//   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//   SPDX-License-Identifier: MIT
// **/
// //==================================================================================================
// #include <eve/function/dec.hpp>
// #include <eve/constant/mzero.hpp>
// #include <tts/tests/relation.hpp>
// #include <tts/tests/types.hpp>
// #include <type_traits>

// TTS_CASE("Check conditional eve::dec return type")
// {
//   TTS_EXPR_IS(eve::dec(Type(), Type()), (Type));
// }

// TTS_CASE("Check conditionaleve::dec behavior")
// {
//   TTS_EQUAL(eve::dec[ Type(1) > Type(0) ](Type(1)), Type(0));
//   TTS_EQUAL(eve::dec[ Type(1) > Type(2) ](eve::Zero<Type>()), Type(0));

//   if constexpr(std::is_signed_v<Type>)
//   {
//     TTS_EQUAL(eve::dec[-Type(1) > Type(0) ](eve::Zero<Type>()), Type(0));
//   }

//   if constexpr(std::is_floating_point_v<Type>)
//   {
//     TTS_EQUAL(eve::dec(eve::Mzero<Type>()), Type(-1));
//     TTS_EQUAL(eve::dec(eve::Zero<Type>()), Type(-1));
//   }
// }

// #endif

//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE("Check eve::dec[condition] return type")
{
  TTS_EXPR_IS( (eve::dec[ Type() ](Type())), (Type));
  TTS_EXPR_IS( (eve::dec[ eve::logical<Type>() ](Type())), (Type));
  TTS_EXPR_IS( (eve::dec[ true ](Type())), (Type));
}

TTS_CASE("Check eve::dec[condition] behavior")
{
  Type tv{2};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  // All basic TRUE
  TTS_EQUAL(eve::dec[ 1 ](tv)     , tv - 1);
  TTS_EQUAL(eve::dec[ 1.0 ](tv)   , tv - 1);
  TTS_EQUAL(eve::dec[ true ](tv)  , tv - 1);
  TTS_EQUAL(eve::dec[ t ](tv)     , tv - 1);

  // All basic FALSE
  TTS_EQUAL(eve::dec[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::dec[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::dec[ false ](tv) , tv);
  TTS_EQUAL(eve::dec[ f ](tv)     , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::dec[ m ](tv) , eve::if_else(m,tv - 1, tv) );
}
