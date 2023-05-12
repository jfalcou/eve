//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/transforms/detail/pr.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/transforms.hpp>
#include <vector>
#include <chrono>

TTS_CASE_TPL("Check fft_ht on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> ar(N), br(N), ai(N), bi(N);
    for(size_t i=0; i < N ; ++i){ br[i] = ar[i] =  i+1; bi[i] = ai[i] = i+2; };
    eve::naive_ft(ar, ai, e_t(1.0), e_t(-1));
    eve::fft_ht(br, bi, e_t(1.0));
    for(size_t i=0; i <N ; ++i){
      TTS_ULP_EQUAL(          ar[i],            br[i] , 10000);
      TTS_ULP_EQUAL(          ai[i],            bi[i] , 10000);
    }
  }
};
