//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  //================================================================================================
  // Interleave pairs of wides
  //================================================================================================
  template<scalar_value T, typename N>
  EVE_FORCEINLINE kumi::tuple<wide<T, N>, wide<T, N>> deinterleave_(EVE_SUPPORTS(sse2_), wide<T,N> v0, wide<T,N> v1) noexcept
  requires (N() >= 4) && x86_abi<abi_t<T,N>>
  {
    using type = wide<T,N>;

    constexpr auto c = categorize<type>();

    if constexpr( c == category::float64x4 && eve::current_api >= eve::avx2 )
    {
      auto a0a1b0b1 = _mm256_permute4x64_pd(v0, _MM_SHUFFLE(3, 1, 2, 0));
      auto b2b3a2a3 = _mm256_permute4x64_pd(v1, _MM_SHUFFLE(2, 0, 3, 1));
      return {_mm256_permute2f128_pd(a0a1b0b1, b2b3a2a3, 0x30),
              _mm256_permute2f128_pd(a0a1b0b1, b2b3a2a3, 0x21)};
    }
    else return deinterleave_(EVE_RETARGET(cpu_),v0,v1);
  }
}
