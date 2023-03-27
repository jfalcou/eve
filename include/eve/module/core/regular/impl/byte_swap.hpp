//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_swap.hpp>
#include <eve/module/core/regular/byte_reverse.hpp>

namespace eve::detail
{
  template<auto N, unsigned_value T>
  EVE_FORCEINLINE auto
  byte_swap_(EVE_SUPPORTS(cpu_), T x, std::integral_constant<size_t, N>) noexcept
  {
    using v_t = element_type_t<T>;
    if constexpr(sizeof(v_t) == 0) return x;
    else return bit_swap(x, std::integral_constant<size_t, N*8>());
  }

  // Masked case
  template<conditional_expr C, unsigned_value U, auto N>
  EVE_FORCEINLINE auto
  byte_swap_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, std::integral_constant<size_t, N> const & n) noexcept
  {
    return mask_op(cond, eve::bit_swap, t, std::integral_constant<size_t, N*8>());
  }
}
