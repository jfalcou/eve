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
  auto sub_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires (rvv_abi<abi_t<T, N>> && !O::contains(mod))
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr (match(c, category::float16) && !_::supports_fp16_vector_ops && !O::contains(widen))
    {
      if constexpr (O::contains_any(lower, upper)) return _::map(sub[opts], a, b);
      else                                         return apply_fp16_as_fp32(sub[opts], a, b);
    }
    else if constexpr (O::contains(left))
    {
      return sub[opts.drop(left)](b, a);
    }
    else if constexpr (O::contains(widen) || (O::contains_any(lower, upper) && floating_value<T>))
    {
      return sub.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains(saturated) && match(c, category::int_))  return wide<T, N>(__riscv_vssub(a, b, N));
    else if constexpr (O::contains(saturated) && match(c, category::uint_)) return wide<T, N>(__riscv_vssubu(a, b, N));
    else if constexpr (match(c, category::float_))                          return wide<T, N>(__riscv_vfsub(a, b, N));
    else                                                                    return wide<T, N>(__riscv_vsub(a, b, N));
  }
}
