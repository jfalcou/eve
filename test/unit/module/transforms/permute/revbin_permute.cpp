//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include <eve/module/transforms.hpp>
#include <eve/module/transforms/detail/pr.hpp>
#include <chrono>

TTS_CASE_TPL("Check revbin_permute", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( eve::cardinal_v<T> == 1)
  {
    for(int n=16; n <= 16; n <<= 2)
    {
      std::vector<int32_t> vi(n), orig(n);
      for(int i=0; i < n ; ++i) vi[i] = i;
      eve::revbin_permute(vi);
      eve::revbin_permute(vi);
      for(int i = 0; i < n; i++) TTS_EQUAL(vi[i], i);
    }
  }
};
