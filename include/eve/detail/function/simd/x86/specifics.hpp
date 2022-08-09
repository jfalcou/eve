//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

namespace eve::detail
{
  //================================================================================================
  // alignr_si256 reconstruction
  //================================================================================================
#if defined(SPY_SIMD_IS_X86_AVX2)
  template<std::size_t Shift> __m256i alignr_si256(__m256i a, __m256i b)
  {
    __m256i b1_a0 = _mm256_permute2x128_si256(a, b, 0x03);
          if constexpr(Shift == 16) return b1_a0;
    else  if constexpr(Shift <  16) return _mm256_alignr_epi8(b1_a0, b, Shift);
    else                            return _mm256_alignr_epi8(a, b1_a0, Shift - 16);
  }
#endif
}
