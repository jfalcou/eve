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

TTS_CASE_TPL("Check naive_ft on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> a(N);
    std::vector<e_t> ref = {28, 1.9296875, 0.44427490234375, 0.16326475143432617
                            , 0.071111109107732773, 0.033298647234914824
                            , 0.016124968505891957, 0.0079360158720316321 };
    for(size_t i=0; i < N ; ++i) a[i] = e_t(i);
    pr("a", a.data(), N);
    eve::aos(eve::naive_zt)(a, e_t(0.5));
    pr("a", a.data(), N);
    for(size_t i=0; i <N ; ++i){
      TTS_ULP_EQUAL(          a[i],            ref[i] , 10000);
    }
    pr("a", a.data(), N);
  }
};
