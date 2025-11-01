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

namespace eve::detail
{
  template<callable_options O, typename T, typename N, typename U>
  EVE_FORCEINLINE logical<wide<T, N>> is_less_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, U b) noexcept
    requires (rvv_abi<abi_t<T, N>> && same_element_type<T, U>)
  {
    if constexpr (O::contains(definitely))
    {
      return is_less.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if      constexpr (match(c, category::int_))   return __riscv_vmslt(a, b, N::value);
      else if constexpr (match(c, category::uint_))  return __riscv_vmsltu(a, b, N::value);
      else if constexpr (match(c, category::float16) && !detail::supports_fp16_vector_ops)
      {
        return apply_fp16_as_fp32(is_less, a, b);
      }
      else if constexpr (match(c, category::float_)) return __riscv_vmflt(a, b, N::value);
    }
  }
}
