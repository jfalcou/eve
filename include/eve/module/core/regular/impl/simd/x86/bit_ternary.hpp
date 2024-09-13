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
  template<std::uint8_t K, scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  bit_ternary_(EVE_REQUIRES(sse2_), O const& opts,
               std::integral_constant<std::uint8_t, K> const & ik,
               wide<T, N> const& x, wide<T, N> const &y, wide<T, N> const &z) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using w_t = wide<T, N>;
    using i_t = as_integer_t<w_t, unsigned>;
    auto a = bit_cast(x, as<i_t>());
    auto b = bit_cast(y, as<i_t>());
    auto c = bit_cast(z, as<i_t>());
    if constexpr  (  current_api < avx512 || sizeof(T) < 4)
    {
      auto doit = [opts, ik](auto a, auto b, auto c){
        if constexpr(K == 0x1b) return bit_or(bit_notand(a, c), bit_notand(c, bit_not(b)));
        if constexpr(K == 0x1d) return bit_or(bit_notand(a, b), bit_notand(b, bit_not(c)));
        if constexpr(K == 0x27) return bit_or(bit_notand(b, c), bit_notand(c, bit_not(a)));
        if constexpr(K == 0x2e) return bit_xor(bit_or(b, c), bit_and(a, b));
        if constexpr(K == 0x35) return bit_or(bit_notand(b, a), bit_notand(a, bit_not(c)));
        if constexpr(K == 0x3a) return bit_or(bit_notand(b, a), bit_notand(a, c));
        if constexpr(K == 0x47) return bit_or(bit_notand(c, b), bit_notand(b, bit_not(a)));
        if constexpr(K == 0x4e) return bit_or(bit_notand(a, c), bit_notand(c, b));
        if constexpr(K == 0x53) return bit_or(bit_notand(c, a), bit_notand(a, bit_not(b)));
        if constexpr(K == 0x72) return bit_or(bit_notand(b, c), bit_notand(c, a));
        if constexpr(K == 0x74) return bit_or(bit_notand(c, b), bit_notand(b, a));
        if constexpr(K == 0x8b) return bit_or(bit_and(b, c),  bit_notand(b, bit_not(a)));
        if constexpr(K == 0x8d) return bit_or(bit_and(c, b), bit_notand(c,bit_not(a)));
        if constexpr(K == 0xa3) return bit_or(bit_and(a, c), bit_notand(a,bit_not(b)));
        if constexpr(K == 0xb1) return bit_or(bit_and(a, c), bit_andnot(bit_not(b), c));
        if constexpr(K == 0xc5) return bit_or(bit_and(a, b), bit_notand(a, bit_not(c)));
        if constexpr(K == 0xd1) return bit_or(bit_not(bit_or(b, c)), bit_and(a, b));
        else return bit_ternary.behavior(cpu_{}, opts, ik, a, b, c);
      };
      return bit_cast(doit(a, b, c), as<w_t>());
    }
    else
    {
      auto doit = [ik, opts](auto x,  auto y,  auto z){
        constexpr auto ca = categorize<i_t>();
        if constexpr( ca == category::uint64x8 ) return _mm512_ternarylogic_epi64(x, y, z, K);
        else if constexpr( ca == category::uint64x4 ) return _mm256_ternarylogic_epi64(x, y, z, K);
        else if constexpr( ca == category::uint64x2 ) return _mm_ternarylogic_epi64(x, y, z, K);
        else if constexpr( ca == category::uint32x16) return _mm512_ternarylogic_epi32(x, y, z, K);
        else if constexpr( ca == category::uint32x8 ) return _mm256_ternarylogic_epi32(x, y, z, K);
        else if constexpr( ca == category::uint32x4 ) return _mm_ternarylogic_epi32(x, y, z, K);
        else return bit_ternary.behavior(cpu_{}, opts, ik, x, y, z);
      };
      return bit_cast(doit(a, b, c), as<w_t>());
    }
  }

  template<std::uint8_t K, scalar_value T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(avx512_), C const& mask, O const& opts, std::integral_constant<std::uint8_t, K> const & ik,
       wide<T, N> const& x, wide<T, N> const& y, wide<T, N> const& z) noexcept requires x86_abi<abi_t<T, N>>
  {
    auto const            s = alternative(mask, x, as(x));
    [[maybe_unused]] auto m = expand_mask(mask, as(x)).storage().value;
    constexpr auto        ca = categorize<wide<T, N>>();

    using w_t = wide<T, N>;
    using i_t = as_integer_t<w_t, unsigned>;
    auto a = bit_cast(x, as<i_t>());
    auto b = bit_cast(y, as<i_t>());
    auto c = bit_cast(z, as<i_t>());
    auto doit = [ik, opts, s, m](auto x,  auto y,  auto z){
      if      constexpr( C::is_complete )               return s;
      else if constexpr( ca == category::uint64x8       ) return _mm512_mask_ternary_logic_epi64(s, m, x, y, z, K);
      else if constexpr( ca == category::uint64x4       ) return _mm256_mask_ternary_logic_epi64(s, m, x, y, z, K);
      else if constexpr( ca == category::uint64x2       ) return _mm_mask_ternary_logic_epi64   (s, m, x, y, z, K);
      else if constexpr( ca == category::uint32x16      ) return _mm512_mask_ternary_logic_epi32(s, m, x, y, z, K);
      else if constexpr( ca == category::uint32x8       ) return _mm256_mask_ternary_logic_epi32(s, m, x, y, z, K);
      else if constexpr( ca == category::uint32x4       ) return _mm_mask_ternary_logic_epi32   (s, m, x, y, z, K);
      else return bit_ternary.behavior(cpu_{}, opts, ik, x, y, z);
    };
      return bit_cast(doit(a, b, c), as<w_t>());
  }
}
