//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/fft/regular/revbin.hpp>


TTS_CASE_TPL("Check revbin", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
//   T x([](auto i,  auto){return i; });
// //   auto pr = [](auto name, auto x){
// //     std::cout << name << " = (";
// //     for(int i=0; i < eve::cardinal_v<T>; ++i) std::cout << x[i] << " ";
// //     std::cout << ")\n";
// //   };
// //   pr(x);
//   std::cout << "x " << x << std::endl;
//   std::cout << "r " << eve::revbin(x)<< std::endl;
  TTS_EQUAL(0, 0);
};
