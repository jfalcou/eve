//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

// TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
// {
//   TTS_EXPR_IS(eve::if_else(T()               , T(), T()), T);
//   TTS_EXPR_IS(eve::if_else(eve::logical<T>() , T(), T()), T);
//   TTS_EXPR_IS(eve::if_else(true              , T(), T()), T);
// }

// TTS_CASE_TPL("Check eve::if_else behavior with arithmetic alternatives", EVE_TYPE)
// {
//   T tv{2};
//   T fv{3};
//   auto t = eve::True<T>();
//   auto f = eve::False<T>();

//   std::cout << tts::type_id<T>() << std::endl;
// //   std::cout << "3" << std::endl;
// //   TTS_EQUAL(eve::if_else(1    , tv, fv), tv);
// //   std::cout << "4" << std::endl;
// //   TTS_EQUAL(eve::if_else(1.0  , tv, fv), tv);
// //   std::cout << "5" << std::endl;
// //   TTS_EQUAL(eve::if_else(true , tv, fv), tv);
//   std::cout << "6" << std::endl;
//   TTS_EQUAL(eve::if_else(t    , tv, fv), tv);
// //   std::cout << "7" << std::endl;
// //   TTS_EQUAL(eve::if_else(0    , tv, fv), fv);
// //   std::cout << "8" << std::endl;
// //   TTS_EQUAL(eve::if_else(0.0  , tv, fv), fv);
// //   std::cout << "9" << std::endl;
// //   TTS_EQUAL(eve::if_else(false, tv, fv), fv);
//   std::cout << "10" << std::endl;
//   TTS_EQUAL(eve::if_else(f    , tv, fv), fv);
//   std::cout << "11" << std::endl;
//   TTS_EQUAL(eve::if_else(fv    , tv, fv), tv);
// }

TTS_CASE_TPL("Check eve::if_else behavior with logical alternatives", EVE_TYPE)
{
  auto t = eve::True<T>();
  auto f = eve::False<T>();
//  T fv{3};

  std::cout << tts::type_id<T>() << std::endl;
//   std::cout << "110" << std::endl;
//   TTS_EQUAL(eve::if_else(1    , t, f), t);
//   std::cout << "111" << std::endl;
//   TTS_EQUAL(eve::if_else(1.0  , t, f), t);
//   std::cout << "112" << std::endl;
//   TTS_EQUAL(eve::if_else(true , t, f), t);
  std::cout << "113" << std::endl;
  TTS_EQUAL(eve::if_else(t    , t, f), t);
//   std::cout << "114" << std::endl;
//   TTS_EQUAL(eve::if_else(0    , t, f), f);
//   std::cout << "115" << std::endl;
//   TTS_EQUAL(eve::if_else(0.0  , t, f), f);
//   std::cout << "116" << std::endl;
//   TTS_EQUAL(eve::if_else(false, t, f), f);
//   std::cout << "117" << std::endl;
//   TTS_EQUAL(eve::if_else(f    , t, f), f);
//   std::cout << "118" << std::endl;
//   TTS_EQUAL(eve::if_else(fv    , t, f), t);
}
