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
#include <eve/module/core/regular/swap_adjacent_groups.hpp>

namespace eve::detail
{
  template<auto N, value T>
  EVE_FORCEINLINE T
  swap_adjacent_(EVE_SUPPORTS(cpu_), T x, std::integral_constant<size_t, N>) noexcept
  {
    using e_t =  element_type_t<T>;
    constexpr auto S = sizeof(e_t);
    if constexpr(N == 0) return x;
    else if constexpr(scalar_value<T> || N >= cardinal_v<T>) return zero(as(x));
    else return swap_adjacent_groups(x, fixed<N>());
  }

  // Masked case
  template<conditional_expr C, ordered_value U, auto N>
  EVE_FORCEINLINE auto
  swap_adjacent_(EVE_SUPPORTS(cpu_), C const& cond
                    , U const& t
                    , std::integral_constant<size_t, N> const & n) noexcept
  {
    return mask_op(cond, eve::bit_swap_adjacent, t, n);
  }
}
