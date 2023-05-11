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
    using e_t = eve::element_type_t<T>;
    using c_t = eve::complex<e_t>;
    for(int n=16; n <= 16; n <<= 2)
    {
      std::vector<e_t> vi(n), orig(n);
      for(int i=0; i < n ; ++i) vi[i] = e_t(i);
      eve::revbin_permute(vi);
      eve::revbin_permute(vi);
      for(int i = 0; i < n; ++i) TTS_EQUAL(vi[i], e_t(i));
//       auto d = vi.data();
//       eve::revbin_permute(eve::algo::as_range(d, d+n));
//       eve::revbin_permute(eve::algo::as_range(d, d+n));
//       for(int i = 0; i < n; ++i) TTS_EQUAL(vi[i], e_t(i));

    }
    for(int n=16; n <= 16; n <<= 2)
    {
      eve::algo::soa_vector<c_t> vi(n), orig(n);
      for(int i=0; i < n ; ++i) vi.set(i, c_t(i, i+1));
      eve::revbin_permute(vi);
      eve::revbin_permute(vi);
      for(int i = 0; i < n; ++i) TTS_EQUAL(vi.get(i),  c_t(i, i+1));
    }


  }
};
