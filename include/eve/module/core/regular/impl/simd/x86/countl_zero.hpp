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
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

#include <iostream>
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

    if constexpr(sizeof(T) >=  4)
    {
      if constexpr( current_api == avx512)
      {
        if constexpr( c == category::uint64x8 ) return r_t(_mm512_lzcnt_epi64(a0));
        else if constexpr( c == category::uint32x16) return r_t(_mm512_lzcnt_epi32(a0));
        else if constexpr( c == category::uint64x4 ) return r_t(_mm256_lzcnt_epi64(a0));
        else if constexpr( c == category::uint32x8 ) return r_t(_mm256_lzcnt_epi32(a0));
        else if constexpr( c == category::uint64x2 ) return r_t(_mm_lzcnt_epi64(a0));
        else if constexpr( c == category::uint32x4 ) return r_t(_mm_lzcnt_epi32(a0));
      }
      else if constexpr( current_api >= sse2 )
      {
        //Inspired from: https://stackoverflow.com/questions/58823140/count-leading-zero-bits-for-each-element-in-avx2-vector-emulate-mm256-lzcnt-ep
        using ri_t       = wide<std::int32_t,N>;
        using ri_t2      = downgrade_t<ri_t>;
        using ru_t2      = downgrade_t<r_t>;
        if constexpr( c == category::uint32x8 ||  c == category::uint32x4 )
        {
          auto    v   = bit_notand(bit_shr(a0, 8), a0);
          v   = bit_cast(convert(bit_cast(v, as<ri_t>{}), as<float>{}), as<r_t>{});
          v   = bit_shr(v, 23);
          auto w   = bit_cast(v, as<ru_t2>{});
          w   = sub[saturated2](158, w);                    // undo bias
          auto v32 = bit_cast(r_t(32u), as<ru_t2>{});
//          return r_t(eve::min(w,v32)); // clamp at 32
          return bit_cast(eve::min(w,v32), as<r_t>());
        }
        else return countl_zero.behavior(cpu_{}, opts, a0);
      }
      else
        return countl_zero.behavior(cpu_{}, opts, a0);
    }
    else
      return countl_zero.behavior(cpu_{}, opts, a0);
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
