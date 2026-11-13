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
#include <eve/traits/apply_fp16.hpp>

namespace eve::_
{
  template<callable_options O, arithmetic_scalar_value T, width_type N>
  auto div_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires (rvv_abi<abi_t<T, N>> && !O::contains(mod))
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr (match(c, category::float16) && !_::supports_fp16_vector_ops && !O::contains(widen))
    {
      if constexpr (O::contains_any(lower, upper)) return _::map(div[opts], a, b);
      else                                         return apply_fp16_as_fp32(div[opts], a, b);
    }
    else if constexpr (O::contains(left))
    {
      return div[opts.drop(left)](b, a);
    }
    else if constexpr (O::contains_any(saturated, upper, lower))
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains_any(toward_zero, upward, downward, to_nearest))
    {
      if constexpr (floating_value<T>) return round[opts](div(a, b));
      else                             return div.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (match(c, category::int_))   return wide<T, N>(__riscv_vdiv(a, b, N));
    else if constexpr (match(c, category::uint_))  return wide<T, N>(__riscv_vdivu(a, b, N));
    else                                           return wide<T, N>(__riscv_vfdiv(a, b, N));
  }
}
