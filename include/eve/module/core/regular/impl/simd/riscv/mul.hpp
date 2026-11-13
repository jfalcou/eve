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
  auto mul_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires (rvv_abi<abi_t<T, N>> && !O::contains(mod))
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr (match(c, category::float16) && !_::supports_fp16_vector_ops && !O::contains(widen))
    {
      if constexpr (O::contains_any(lower, upper)) return _::map(mul[opts], a, b);
      else                                         return apply_fp16_as_fp32(mul[opts], a, b);
    }
    else if constexpr (O::contains(widen) || (O::contains_any(lower, upper) && floating_value<T>))
    {
      return mul.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains(saturated) && std::integral<T>)
    {
      return mul.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (match(c, category::float_)) return wide<T, N>(__riscv_vfmul(a, b, N));
    else                                           return wide<T, N>(__riscv_vmul(a, b, N));
  }
}
