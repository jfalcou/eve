//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

template<scalar_value T, typename N>
EVE_FORCEINLINE auto
abs_(EVE_SUPPORTS(rvv_), wide<T, N> const& a) noexcept -> wide<T, N>
requires rvv_abi<abi_t<T, N>> && (match(categorize<wide<T, N>>(), category::float_))
{
  return __riscv_vfabs(a, N::value);
}

template<scalar_value T, typename N>
EVE_FORCEINLINE auto
abs_(EVE_SUPPORTS(rvv_), wide<T, N> const& a) noexcept -> wide<T, N>
requires rvv_abi<abi_t<T, N>> && (match(categorize<wide<T, N>>(), category::int_))
{
  wide<T, N>          negative_values     = __riscv_vneg(a, N::value);
  logical<wide<T, N>> need_to_change_mask = self_less(a, static_cast<T>(0));
  return if_else(need_to_change_mask, negative_values, a);
}

template<conditional_expr C, scalar_value T, typename N>
EVE_FORCEINLINE auto
abs_(EVE_SUPPORTS(rvv_), C const& cx, wide<T, N> const& v) noexcept -> wide<T, N>
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( C::is_complete ) return abs_(EVE_RETARGET(cpu_), cx, v);
  else
  {
    auto mask = expand_mask(cx, as<wide<T, N>> {});
    if constexpr( match(c, category::float_) ) { return __riscv_vfabs_tumu(mask, v, v, N::value); }
    if constexpr( match(c, category::int_) )
    {
      wide<T, N>          negative_values     = __riscv_vneg(v, N::value);
      logical<wide<T, N>> need_to_change_mask = self_less(v, static_cast<T>(0));
      logical<wide<T, N>> mask_to_update      = __riscv_vmand(mask, need_to_change_mask, N::value);
      return if_else(mask_to_update, negative_values, v);
    }
  }
}
}
