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
  EVE_FORCEINLINE logical<wide<T, N>> is_less_equal_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, U b) noexcept
    requires (rvv_abi<abi_t<T, N>> && same_element_type<T, U>)
  {
    if constexpr (O::contains(almost))
    {
      return is_less_equal.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if      constexpr (match(c, category::int_))   return __riscv_vmsle(a, b, N::value);
      else if constexpr (match(c, category::uint_))  return __riscv_vmsleu(a, b, N::value);
      else if constexpr (match(c, category::float16) && !detail::supports_fp16_vector_ops)
      {
        return apply_fp16_as_fp32(is_less_equal, a, b);
      }
      else if constexpr (match(c, category::float_)) return __riscv_vmfle(a, b, N::value);
    }
  }
}
