//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> countl_zero_(EVE_REQUIRES(sse2_),
                                          O const& opts,
                                          wide<T, N> a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using r_t        = wide<T, N>;
    constexpr auto c = categorize<r_t>();

    if constexpr( current_api < avx512 || sizeof(T) < 4 ) return countl_zero.behavior(cpu_{}, opts, a0);
    else if constexpr( c == category::uint64x8 ) return r_t(_mm512_lzcnt_epi64(a0));
    else if constexpr( c == category::uint32x16) return r_t(_mm512_lzcnt_epi32(a0));
    else if constexpr( c == category::uint64x4 ) return r_t(_mm256_lzcnt_epi64(a0));
    else if constexpr( c == category::uint32x8 ) return r_t(_mm256_lzcnt_epi32(a0));
    else if constexpr( c == category::uint64x2 ) return r_t(_mm_lzcnt_epi64(a0));
    else if constexpr( c == category::uint32x4 ) return r_t(_mm_lzcnt_epi32(a0));
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<int S, conditional_expr C, integral_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> countl_zero_(EVE_REQUIRES(avx512_),
                                          C const          & cx,
                                          O const          & opts,
                                          wide<T, N> const & a0) noexcept requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    auto src = alternative(cx, a0, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( C::is_complete)                return src;
    else if constexpr( c == category::uint64x8 ) return r_t(_mm512_mask_lzcnt_epi64(src, m, a0));
    else if constexpr( c == category::uint32x16) return r_t(_mm512_mask_lzcnt_epi32(src, m, a0));
    else if constexpr( c == category::uint64x4 ) return r_t(_mm256_mask_lzcnt_epi64(src, m, a0));
    else if constexpr( c == category::uint32x8 ) return r_t(_mm256_mask_lzcnt_epi32(src, m, a0));
    else if constexpr( c == category::uint64x2 ) return r_t(_mm_mask_lzcnt_epi64(src, m, a0));
    else if constexpr( c == category::uint32x4 ) return r_t(_mm_mask_lzcnt_epi32(src, m, a0));
    else return countl_zero.behavior(cpu_{}, opts, a0);
  }
}
