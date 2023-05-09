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
    size_t N = 262144;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> a(N), orig(N), naiv(N);
    for(size_t i=0; i < N ; ++i) naiv[i] = orig[i] = a[i] = i+1;
    eve::aos(eve::small_df_fht)(naiv, e_t(1.0));
    eve::aos(eve::large_df_fht)(a, e_t(1.0), true);
    for(size_t i=0; i <N ; ++i){
      TTS_RELATIVE_EQUAL(a[i],naiv[i], 0.001);
    }
    eve::aos(eve::small_df_fht)(a, e_t(2)/(N)); //inverse ht
    for(size_t i=0; i <N ; ++i){
      TTS_RELATIVE_EQUAL(a[i],orig[i], 0.0001);
    }
  }
};
