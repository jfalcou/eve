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
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/is_less.hpp>


namespace eve::detail
{

  template<callable_options O, floating_scalar_value T, typename N,  typename F>
  EVE_FORCEINLINE logical<wide<T, N>>
  compare_absolute_(EVE_REQUIRES(sve_), O const& opts,
                    wide<T, N> v, wide<T, N> w,  F f) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    auto m = sve_true<T>();
    if      constexpr(F{} == is_less_equal)    return svacle(m, v, w);
    else if constexpr(F{} == is_less)          return svaclt(m, v, w);
    else if constexpr(F{} == is_greater_equal) return svacge(m, v, w);
    else if constexpr(F{} == is_less_equal)    return svacgt(m, v, w);
    else return compare_absolute.behavior(cpu_{}, opts, v, w, f);
  }

  template<callable_options O, floating_scalar_value T, typename N, conditional_expr C,  typename F>
  EVE_FORCEINLINE logical<wide<T, N>> compare_absolute_(EVE_REQUIRES(sve_), C const& mask, O const& opts,
                                  wide<T, N> v, wide<T, N> w, F f) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    auto const alt = alternative(mask, v, as(to_logical(v)));
    if constexpr( C::is_complete ) return alt;
    else if  constexpr (!C::has_alternative)
    {
      auto m = expand_mask(mask, as(v));
      if      constexpr(F{} ==  is_less_equal)   return svacle(m, v, w);
      else if constexpr(F{} == is_less)          return svaclt(m, v, w);
      else if constexpr(F{} == is_greater_equal) return svacge(m, v, w);
      else if constexpr(F{} == is_less_equal)    return svacgt(m, v, w);
      else return compare_absolute.behavior(cpu_{}, opts, v, w, f);
    }
    else return compare_absolute.behavior(cpu_{}, opts, v, w, f);
  }
}
