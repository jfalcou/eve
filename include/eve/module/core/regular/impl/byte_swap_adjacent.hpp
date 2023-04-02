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
#include <eve/module/core/regular/bit_swap_adjacent.hpp>
#include <eve/module/core/regular/byte_reverse.hpp>

namespace eve::detail
{
  template<unsigned_value T,  integral_value N>
  EVE_FORCEINLINE auto
  byte_swap_adjacent_(EVE_SUPPORTS(cpu_), T x, N n) noexcept
  {
    using v_t = element_type_t<T>;
    if constexpr(sizeof(v_t) == 0) return x;
    else return bit_swap_adjacent(x, n*8);
  }

  // Masked case
  template<conditional_expr C, unsigned_value U,  integral_value N>
  EVE_FORCEINLINE auto
  byte_swap_adjacent_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, N const & n) noexcept
  {
    return mask_op(cond, eve::bit_swap_adjacent, t, n*8);
  }
}
