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
#include <eve/module/transforms.hpp>
#include <vector>

TTS_CASE_TPL("Check naive_cyclic_convolution on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = eve::element_type_t<T>;
    std::vector<e_t> a(N), b(N), c(2*N);
    std::vector<e_t> ref(N*2);
    for(size_t i=0; i < N ; ++i) {ref[2*N-i-2] = ref[i] = e_t(i+1); };

    for(size_t i=0; i < N ; ++i) b[i] = a[i] = 1;
    pr("a   ", a.data(), N);
    pr("b   ", b.data(), N);
    pr("ref ", ref.data(), 2*N);
    eve::naive_linear_convolution(a, b, c);
    pr("c   ", c.data(), 2*N);
    for(size_t i=0; i <2*N ; ++i){
      TTS_EQUAL(c[i],ref[i]);
    }
  }
};
