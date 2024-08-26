//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
  template<std::uint8_t K, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  bit_ternary_(EVE_REQUIRES(avx512_), O const& opts, std::integral_constant<std::uint8_t, K> const & ik,
               wide<T, N> const& x, wide<T, N> const &y, wide<T, N> const &z) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
          if constexpr( c == category::int64x8 ) return _mm512_ternarylogic_epi64(x, y, z, ik);
    else  if constexpr( c == category::int64x4 ) return _mm256_ternarylogic_epi64(x, y, z, ik);
    else  if constexpr( c == category::int64x2 ) return _mm_ternarylogic_epi64(x, y, z, ik);
    else  if constexpr( c == category::int32x16) return _mm512_ternarylogic_epi32(x, y, z, ik);
    else  if constexpr( c == category::int32x8 ) return _mm256_ternarylogic_epi32(x, y, z, ik);
    else  if constexpr( c == category::int32x4 ) return _mm_ternarylogic_epi32(x, y, z, ik);
    else  return bit_ternary.behavior(cpu_{}, opts, ik, x, y, z);
  }

  template<std::uint8_t K, arithmetic_scalar_value T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(avx512_), C const& mask, O const& opts, std::integral_constant<std::uint8_t, K> const & ik,
       wide<T, N> const& x, wide<T, N> const& y, wide<T, N> const& z) noexcept requires x86_abi<abi_t<T, N>>
  {
    auto const            s = alternative(mask, x, as(x));
    [[maybe_unused]] auto m = expand_mask(mask, as(x)).storage().value;
    constexpr auto        c = categorize<wide<T, N>>();

    if      constexpr( C::is_complete )               return s;
    else if constexpr( c == category::int64x8       ) return _mm512_mask_ternary_logic_epi64(s, m, x, y, z, ik);
    else if constexpr( c == category::int64x4       ) return _mm256_mask_ternary_logic_epi64(s, m, x, y, z, ik);
    else if constexpr( c == category::int64x2       ) return _mm_mask_ternary_logic_epi64   (s, m, x, y, z, ik);
    else if constexpr( c == category::int32x16      ) return _mm512_mask_ternary_logic_epi32(s, m, x, y, z, ik);
    else if constexpr( c == category::int32x8       ) return _mm256_mask_ternary_logic_epi32(s, m, x, y, z, ik);
    else if constexpr( c == category::int32x4       ) return _mm_mask_ternary_logic_epi32   (s, m, x, y, z, ik);
    else                                              return bit_ternary.behavior(cpu_{}, opts, ik, x, y, z);
  }
}
