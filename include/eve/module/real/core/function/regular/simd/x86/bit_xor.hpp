//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve ::detail
{
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> bit_xor_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v0,  wide<T, N> const &v1) noexcept
  requires x86_abi<abi_t<T, N>> && (sizeof(T) >= 4) // TO DO make it work for 1 and 2
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return bit_xor_(EVE_RETARGET(cpu_),cx,v0, v1);
    }
    else
    {
      auto src  = alternative(cx,v0,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;
            if constexpr(c == category::float32x16) return _mm512_mask_xor_ps   (src,m,v0,v1);
      else  if constexpr(c == category::float64x8 ) return _mm512_mask_xor_pd   (src,m,v0,v1);
      else  if constexpr(c && category::float_    ) return if_else(cx,eve::bit_xor(v0, v1),src);
      else  if constexpr(c == category::int64x8   ) return _mm512_mask_xor_epi64(src,m,v0,v1);
      else  if constexpr(c == category::int64x4   ) return _mm256_mask_xor_epi64(src,m,v0,v1);
      else  if constexpr(c == category::int64x2   ) return _mm_mask_xor_epi64   (src,m,v0,v1);
      else  if constexpr(c == category::int32x16  ) return _mm512_mask_xor_epi32(src,m,v0,v1);
      else  if constexpr(c == category::int32x8   ) return _mm256_mask_xor_epi32(src,m,v0,v1);
      else  if constexpr(c == category::int32x4   ) return _mm_mask_xor_epi32   (src,m,v0,v1);
      else  if constexpr(c == category::int_      ) return if_else(cx,eve::bit_xor(v0, v1),src);
      else  if constexpr(c == category::uint64x8  ) return _mm512_mask_xor_epi64(src,m,v0,v1);
      else  if constexpr(c == category::uint64x4  ) return _mm256_mask_xor_epi64(src,m,v0,v1);
      else  if constexpr(c == category::uint64x2  ) return _mm_mask_xor_epi64   (src,m,v0,v1);
      else  if constexpr(c == category::uint32x16 ) return _mm512_mask_xor_epi32(src,m,v0,v1);
      else  if constexpr(c == category::uint32x8  ) return _mm256_mask_xor_epi32(src,m,v0,v1);
      else  if constexpr(c == category::uint32x4  ) return _mm_mask_xor_epi32   (src,m,v0,v1);
      else  if constexpr(c == category::uint_     ) return if_else(cx,eve::bit_xor(v0, v1),src);
    }
  }
}
