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

namespace eve::detail
{
template<conditional_expr C, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
div_(EVE_SUPPORTS(rvv_), C const& cx, wide<T, N> const& v, wide<T, N> const& w) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete ) { return div_(EVE_RETARGET(cpu_), cx, v, w); }
  else
  {
    if constexpr( !C::has_alternative )
    {
      auto           m = expand_mask(cx, as<wide<T, N>> {});
      constexpr auto c = categorize<wide<T, N>>();
      if constexpr( match(c, category::int_) ) return __riscv_vdiv_tumu(m, v, v, w, N::value);
      else if constexpr( match(c, category::uint_) ) return __riscv_vdivu_tumu(m, v, v, w, N::value);
      else if constexpr( match(c, category::float_) ) return __riscv_vfdiv_tumu(m, v, v, w, N::value);
    }
    else return div_(EVE_RETARGET(cpu_), cx, v, w);
  }
}
}
