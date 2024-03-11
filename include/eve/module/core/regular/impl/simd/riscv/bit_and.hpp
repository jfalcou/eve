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
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
namespace eve ::detail
{
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
bit_and_(EVE_SUPPORTS(rvv_), C const& cx, wide<T, N> const& v0, wide<T, N> const& v1) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return bit_and_(EVE_RETARGET(cpu_), cx, v0, v1);
  }
  else
  {
    auto m                 = expand_mask(cx, as<wide<T, N>> {});
    using sign             = unsigned;
    using out_part_scalar  = as_integer_t<T, sign>;
    using out_part_wide    = wide<out_part_scalar, N>;
    auto          part_tgt = as<out_part_wide> {};
    auto          v0_int   = bit_cast(v0, part_tgt);
    auto          v1_int   = bit_cast(v1, part_tgt);
    out_part_wide part_res = __riscv_vand_tumu(m, v0_int, v0_int, v1_int, N::value);
    return bit_cast(part_res, as<wide<T, N>> {});
  }
}
// -----------------------------------------------------------------------------------------------
// Masked case
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                bit_and_(EVE_SUPPORTS(rvv_), wide<T, N> const                &v0, wide<T, N> const                &v1) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using sign             = unsigned;
  using out_part_scalar  = as_integer_t<T, sign>;
  using out_part_wide    = wide<out_part_scalar, N>;
  auto          part_tgt = as<out_part_wide> {};
  auto          v0_int   = bit_cast(v0, part_tgt);
  auto          v1_int   = bit_cast(v1, part_tgt);
  out_part_wide part_res = __riscv_vand(v0_int, v1_int, N::value);
  return bit_cast(part_res, as<wide<T, N>> {});
}
}
