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
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve::detail
{

  template<auto S, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  roundscale_(EVE_REQUIRES(avx512_),
             wide<T, N> const & a0,
             O          const & o,
             std::integral_constant<int, S> ) noexcept requires x86_abi<abi_t<T, N>>
  {
    return roundscale[true_(as(a0))][o](a0, S);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case

  template<auto S, conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_REQUIRES(avx512_),
                                        C          const &mask,
                                        O          const &,
                                        wide<T, N> const &a0,
                                        std::integral_constant<int, S> const &) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, a0, as(a0));

    if constexpr( C::is_complete)  return alt;
    else
    {
      auto          src = alternative(mask, a0, as<wide<T, N>> {});
      auto          m   = expand_mask(mask, as<wide<T, N>> {}).storage().value;
      constexpr int s   = ((S) << 4);

      auto call = [] <int V >(auto src,  auto m, auto a0){
        constexpr auto c = categorize<wide<T, N>>();

        if      constexpr( c == category::float32x16) return _mm512_mask_roundscale_ps(src, m, a0, s+V);
        else if constexpr( c == category::float64x8 ) return _mm512_mask_roundscale_pd(src, m, a0, s+V);
        else if constexpr( c == category::float32x8 ) return _mm256_mask_roundscale_ps(src, m, a0, s+V);
        else if constexpr( c == category::float64x4 ) return _mm256_mask_roundscale_pd(src, m, a0, s+V);
        else if constexpr( c == category::float32x4 ) return _mm_mask_roundscale_ps(src, m, a0, s+V);
        else if constexpr( c == category::float64x2 ) return _mm_mask_roundscale_pd(src, m, a0, s+V);
      };

      if       constexpr(O::contains(to_nearest2))  return call<0>(src, m, a0);
      else if  constexpr(O::contains(downward2))    return call<1>(src, m, a0);
      else if  constexpr(O::contains(upward2))      return call<2>(src, m, a0);
      else if  constexpr(O::contains(toward_zero2)) return call<3>(src, m, a0);
    }
  }
}
