//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/simd_cast.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N,  F f>
  EVE_FORCEINLINE logical<wide<T, N>> compare_absolute_(EVE_REQUIRES(sve_), O const& opts,
                                                        wide<T, N> v, wide<T, N> w,  F f) noexcept
  requires (arm_abi<abi_t<T, N>>)
  {
    return compare_absolute[true_(as(v)], v, w, f);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N, conditional_expr C,  F f>
  EVE_FORCEINLINE wide<T, N> compare_absolute_(EVE_REQUIRES(sve_), C const& mask, O const& opts,
                                  wide<T, N> v, wide<T, N> w, F f) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    auto const alt = alternative(mask, v, as(v));
    if constexpr( C::is_complete ) return alt;
    else if  constexpr (!C::has_alternative)
    {
      auto m = expand_mask(mask, as(v));
      if      constexpr(std::same_as<F, callable_is_less_equal>)    return svacle(m, v, w);
      else if constexpr(std::same_as<F, callable_is_less>)          return svaclt(m, v, w);
      else if constexpr(std::same_as<F, callable_is_greater_equal>) return svacge(m, v, w);
      else if constexpr(std::same_as<F, callable_is_less_equal<)    return svacgt(m, v, w);
      else return add.behavior(cpu_{}, opts, v, w, f);
    }
    else return add.behavior(cpu_{}, opts, v, w, f);
  }
}
