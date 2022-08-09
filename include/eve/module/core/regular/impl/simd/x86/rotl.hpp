//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// avx512 implementation
template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
EVE_FORCEINLINE wide<T, N>
                rotl_(EVE_SUPPORTS(avx512_), wide<T, N> a0, wide<I, N> a1) noexcept
    requires(sizeof(T) >= 4 && x86_abi<abi_t<T, N>>)
{
  using r_t        = wide<T, N>;
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( c == category::int32x16 ) return r_t(_mm512_rolv_epi32(a0, a1));
  else if constexpr( c == category::int64x8 ) return r_t(_mm512_rolv_epi64(a0, a1));
  else if constexpr( c == category::int32x8 ) return r_t(_mm256_rolv_epi32(a0, a1));
  else if constexpr( c == category::int64x4 ) return r_t(_mm256_rolv_epi64(a0, a1));
  else if constexpr( c == category::int32x4 ) return r_t(_mm_rolv_epi32(a0, a1));
  else if constexpr( c == category::int64x2 ) return r_t(_mm_rolv_epi64(a0, a1));
  else if constexpr( c == category::uint32x16 ) return r_t(_mm512_rolv_epi32(a0, a1));
  else if constexpr( c == category::uint64x8 ) return r_t(_mm512_rolv_epi64(a0, a1));
  else if constexpr( c == category::uint32x8 ) return r_t(_mm256_rolv_epi32(a0, a1));
  else if constexpr( c == category::uint64x4 ) return r_t(_mm256_rolv_epi64(a0, a1));
  else if constexpr( c == category::uint32x4 ) return r_t(_mm_rolv_epi32(a0, a1));
  else if constexpr( c == category::uint64x2 ) return r_t(_mm_rolv_epi64(a0, a1));
}

// -----------------------------------------------------------------------------------------------
// masked avx512 implementation
template<conditional_expr C, integral_real_scalar_value T, integral_real_scalar_value I, typename N>
EVE_FORCEINLINE wide<T, N>
                rotl_(EVE_SUPPORTS(avx512_), C const                &cx, wide<T, N> a0, wide<I, N> a1) noexcept
    requires(sizeof(T) >= 4 && x86_abi<abi_t<T, N>>)
{
  using r_t        = wide<T, N>;
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return rotl_(EVE_RETARGET(cpu_), cx, a0, a1);
  }
  else
  {
    auto src = alternative(cx, a0, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::int32x16 ) return r_t(_mm512_rolv_epi32(src, m, a0, a1));
    else if constexpr( c == category::int64x8 ) return r_t(_mm512_rolv_epi64(src, m, a0, a1));
    else if constexpr( c == category::int32x8 ) return r_t(_mm256_rolv_epi32(src, m, a0, a1));
    else if constexpr( c == category::int64x4 ) return r_t(_mm256_rolv_epi64(src, m, a0, a1));
    else if constexpr( c == category::int32x4 ) return r_t(_mm_rolv_epi32(src, m, a0, a1));
    else if constexpr( c == category::int64x2 ) return r_t(_mm_rolv_epi64(src, m, a0, a1));
    else if constexpr( c == category::uint32x16 ) return r_t(_mm512_rolv_epi32(src, m, a0, a1));
    else if constexpr( c == category::uint64x8 ) return r_t(_mm512_rolv_epi64(src, m, a0, a1));
    else if constexpr( c == category::uint32x8 ) return r_t(_mm256_rolv_epi32(src, m, a0, a1));
    else if constexpr( c == category::uint64x4 ) return r_t(_mm256_rolv_epi64(src, m, a0, a1));
    else if constexpr( c == category::uint32x4 ) return r_t(_mm_rolv_epi32(src, m, a0, a1));
    else if constexpr( c == category::uint64x2 ) return r_t(_mm_rolv_epi64(src, m, a0, a1));
  }
}
}
