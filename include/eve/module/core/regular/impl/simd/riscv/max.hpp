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

template<conditional_expr C, typename T, typename N>
EVE_FORCEINLINE wide<T, N>
                max_(EVE_SUPPORTS(rvv_), C const                &cx, wide<T, N> v, wide<T, N> w) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete ) { return max_(EVE_RETARGET(cpu_), cx, v, w); }
  else
  {
    if constexpr( !C::has_alternative )
    {
      auto           m = expand_mask(cx, as<wide<T, N>> {});
      constexpr auto c = categorize<wide<T, N>>();
      if constexpr( match(c, category::float_) ) return __riscv_vfmax_tumu(m, v, v, w, N::value);
      else if constexpr( match(c, category::int_) ) return __riscv_vmax_tumu(m, v, v, w, N::value);
      else if constexpr( match(c, category::uint_) ) return __riscv_vmaxu_tumu(m, v, v, w, N::value);
    }
    else return max_(EVE_RETARGET(cpu_), cx, v, w);
  }
}
}
