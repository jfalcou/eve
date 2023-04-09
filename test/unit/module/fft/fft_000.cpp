//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/fft.hpp>


TTS_CASE_WITH ( "Check behavior of naive on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0))
              )
<typename T>(T const& , T const&  )
{
   using e_t = typename T::value_type;
   if constexpr(sizeof(e_t) == 4 && eve::cardinal_v<e_t> == 1)
   {
     auto pr = [](auto name,  auto n){
       std::cout << name << "= (";
       for(size_t i=0; i < n.size()-1; ++i) std::cout << n[i] << ",  ";
       std::cout << n[n.size()-1] << ")\n";
     };

     size_t n = 1u << 6;
     using e_t = typename T::value_type;
     using c_t = eve::complex<e_t>;
     std::cout << tts::typename_<e_t> << std::endl;
     std::cout << tts::typename_<c_t> << std::endl;
     std::vector<c_t> a(n);
     for(size_t i=0; i < n ; ++i) a[i] = c_t(i, 0);
//  a[0] = c_t(1, 0);
     pr("a = ", a);

     TTS_EQUAL(0, 0);
     auto c = eve::fft_000(a);
     pr("c = ", c);
   }
};
