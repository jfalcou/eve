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
  template<callable_options O, typename T, typename N, typename U>
  EVE_FORCEINLINE logical<wide<T, N>> is_equal_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, U b) noexcept
    requires (rvv_abi<abi_t<T, N>> && (std::same_as<wide<T, N>, U> || scalar_value<U>))
  {
    constexpr auto c = categorize<wide<T, N>>();

    if      constexpr (O::contains_any(almost, numeric)) return is_equal.behavior(cpu_{}, opts, a, b);
    else if constexpr (match(c, category::integer_))     return __riscv_vmseq(a, b, N::value);
    else if constexpr (match(c, category::float_))       return __riscv_vmfeq(a, b, N::value);
  }

  template<callable_options O, typename T, typename N, scalar_value U>
  EVE_FORCEINLINE logical<wide<T, N>> is_equal_(EVE_REQUIRES(rvv_), O const& opts, U a, wide<T, N> b) noexcept
    requires (rvv_abi<abi_t<T, N>>)
  {
    return is_equal.behavior(current_api, opts, b, a);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_equal_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
  requires(rvv_abi<abi_t<T, N>>)
  {
    return __riscv_vmxnor(a, b, N::value);
  }
}
