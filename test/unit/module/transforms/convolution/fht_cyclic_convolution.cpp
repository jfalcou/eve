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
    size_t N = 16;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = eve::element_type_t<T>;
    std::vector<e_t> a(N), b(N),b1(N), c(N);
    std::vector<e_t> ref(N);
    for(size_t i=0; i < N ; ++i)  b[i] = a[i] = i;
    pr("a", a.data(), N);
    pr("b", b.data(), N);
    eve::naive_cyclic_convolution(a, b, ref);
    eve::fht_cyclic_convolution(a, b, c);
    pr("c", c.data(), N);
    pr("ref", ref.data(), N);
    for(size_t i=0; i <N ; ++i){
      TTS_RELATIVE_EQUAL(c[i],ref[i], 200*eve::eps(eve::as<e_t>()));
    }
  }
};
