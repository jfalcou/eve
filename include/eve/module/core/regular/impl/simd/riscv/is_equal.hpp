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
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_equal_(EVE_REQUIRES(rvv_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires(rvv_abi<abi_t<T, N>>)
  {
    if constexpr( O::contains(almost) || O::contains(numeric))
    {
      return is_equal[opts].retarget(cpu_{}, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();
      if      constexpr( match(c, category::integer_) ) return __riscv_vmseq(a, b, N::value);
      else if constexpr( match(c, category::float_)   ) return __riscv_vmfeq(a, b, N::value);
    }
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_equal_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
  requires(rvv_abi<abi_t<T, N>>)
  {
    return __riscv_vmxnor(a, b, N::value);
  }
}