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
min_(EVE_SUPPORTS(rvv_), wide<T, N> const& a, wide<T, N> const& b) noexcept -> wide<T, N>
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::float_) ) return __riscv_vfmin_tu(a, a, b, N::value);
  else if constexpr( match(c, category::int_) )
  {
    wide<T, N> res = __riscv_vmin_tu(a, a, b, N::value);
    return res;
  }
  else if constexpr( match(c, category::uint_) ) return __riscv_vminu_tu(a, a, b, N::value);
}

template<conditional_expr C, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(rvv_), C const& cx, wide<T, N> const& v, wide<T, N> const& w) noexcept
    -> wide<T, N>
{
  auto           mask = expand_mask(cx, as<wide<T, N>> {});
  constexpr auto c    = categorize<wide<T, N>>();
  if constexpr( match(c, category::float_) ) return __riscv_vfmin_tumu(mask, v, v, w, N::value);
  else if constexpr( match(c, category::int_) ) return __riscv_vmin_tumu(mask, v, v, w, N::value);
  else if constexpr( match(c, category::uint_) ) return __riscv_vminu_tumu(mask, v, v, w, N::value);
}

}
