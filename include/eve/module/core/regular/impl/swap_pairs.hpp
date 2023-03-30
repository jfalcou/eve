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
#include <eve/forward.hpp>

namespace eve::detail
{
  template<value T, auto I0, auto I1>
  EVE_FORCEINLINE T
  swap_pairs_(EVE_SUPPORTS(cpu_), T x
                  , std::integral_constant<size_t, I0> const & i0
                  , std::integral_constant<size_t, I1> const & i1 ) noexcept
  {
    constexpr size_t C = cardinal_v<T>;
    EVE_ASSERT((I0 < C) && (I1 < C), "some index(es) are out or range");
    if constexpr(simd_value<T>)
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      constexpr size_t C = cardinal_v<T>;
      EVE_ASSERT(I0 < C && I1 < C, "some index(es) are out or range");
      auto p = [](auto i,  auto){
       return (i == I0) ? I1 :(i == I1 ? I0 : i) ;
      };
      return eve::shuffle(x, eve::as_pattern(p));
    }
    else if constexpr(scalar_value<T>)
    {
      EVE_ASSERT(I0 < 1 && I1 < 1, "some index(es) are out or range");
      return x;
    }
  }

  // Masked case
  template<conditional_expr C, value T, auto I0, auto I1>
  EVE_FORCEINLINE auto
  swap_pairs_(EVE_SUPPORTS(cpu_), C const& cond, T const& t
                  , std::integral_constant<size_t, I0> const & i0
                  , std::integral_constant<size_t, I1> const & i1 ) noexcept
  {
    return mask_op(cond, eve::swap_pairs, t, i0, i1);
  }
}
