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
//   TTS_EXPR_IS(eve::dec(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
// }

// TTS_CASE("Check conditionaleve::dec behavior")
// {
//   TTS_EQUAL(eve::dec[ EVE_TYPE(1) > EVE_TYPE(0) ](EVE_TYPE(1)), EVE_TYPE(0));
//   TTS_EQUAL(eve::dec[ EVE_TYPE(1) > EVE_TYPE(2) ](eve::Zero<EVE_TYPE>()), EVE_TYPE(0));

//   if constexpr(std::is_signed_v<EVE_VALUE>)
//   {
//     TTS_EQUAL(eve::dec[-EVE_TYPE(1) > EVE_TYPE(0) ](eve::Zero<EVE_TYPE>()), EVE_TYPE(0));
//   }

//   if constexpr(std::is_floating_point_v<EVE_VALUE>)
//   {
//     TTS_EQUAL(eve::dec(eve::Mzero<EVE_TYPE>()), EVE_TYPE(-1));
//     TTS_EQUAL(eve::dec(eve::Zero<EVE_TYPE>()), EVE_TYPE(-1));
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
  TTS_EXPR_IS( (eve::dec[ EVE_TYPE() ](EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::dec[ eve::logical<EVE_TYPE>() ](EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS( (eve::dec[ true ](EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check eve::dec[condition] behavior")
{
  EVE_TYPE tv{2};
  auto t = eve::True<EVE_TYPE>();
  auto f = eve::False<EVE_TYPE>();

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
  eve::as_logical_t<EVE_TYPE> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::dec[ m ](tv) , eve::if_else(m,tv - 1, tv) );
}
