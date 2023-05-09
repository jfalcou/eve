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

TTS_CASE_TPL("Check naive_ht on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> a(N), orig(N), naiv(N);
    for(size_t i=0; i < N ; ++i) naiv[i] = orig[i] = a[i] = i+1;
    pr("naiv  ", naiv.data(), 8);
    eve::aos(eve::naive_ht)(naiv, e_t(1.0));
    pr("naiv  ", naiv.data(), 8);
     pr("a  ", a.data(), 8);
     eve::aos(eve::small_dt_fht)(a, e_t(1.0), true);
    pr("a  ", a.data(), 8);
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],naiv[i], 100*eve::eps(eve::as<e_t>()));
    }
    eve::aos(eve::naive_ht)(a, e_t(2)/(N)); //inverse ht
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],orig[i], 100*eve::eps(eve::as<e_t>()));
    }
  }
};
