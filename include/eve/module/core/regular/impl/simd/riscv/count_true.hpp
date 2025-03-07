//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, conditional_expr C, scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(rvv_), C const& cx, O const&, logical<wide<T, N>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    if constexpr (C::is_complete)
    {
      if constexpr (!C::is_inverted) return 0;
      else return __riscv_vcpop(v, N::value);
    }
    else
    {
      auto const m = cx.mask(as<wide<T, N>> {});
      return __riscv_vcpop(m, v, N::value);
    }
  }

  template<callable_options O, conditional_expr C, scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(rvv_), C const& cx, O const& opts, top_bits<logical<wide<T, N>>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    return count_true_(EVE_TARGETS(rvv_), cx, opts, v.storage);
  }

  template<callable_options O, scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(rvv_), O const& opts, logical<wide<T, N>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    return count_true_(EVE_TARGETS(rvv_), ignore_none, opts, v);
  }

  template<callable_options O, scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(rvv_), O const& opts, top_bits<logical<wide<T, N>>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    return count_true_(EVE_TARGETS(rvv_), ignore_none, opts, v.storage);
  }
}
