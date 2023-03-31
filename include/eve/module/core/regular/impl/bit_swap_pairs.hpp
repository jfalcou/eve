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
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/bit_unset.hpp>

namespace eve::detail
{
  template<unsigned_value T, unsigned_value I0, unsigned_value I1>
  EVE_FORCEINLINE T
  bit_swap_pairs_(EVE_SUPPORTS(cpu_), T a, I0 i0,  I1 i1) noexcept
  {
    constexpr size_t S8 = sizeof(element_type_t<T>)*8;
    EVE_ASSERT(i0 < S8 && i1 < S8, "some indexes are out or range");
    auto x = bit_and(bit_xor(bit_shr(a, i0), bit_shr(a, i1)), one(as(a)));
    a ^= bit_shl(x, i1);
    a ^= bit_shl(x, i0);
    return a;
  }

  // Masked case
  template<conditional_expr C, unsigned_value T, unsigned_value I0, unsigned_value I1>
  EVE_FORCEINLINE auto
  bit_swap_pairs_(EVE_SUPPORTS(cpu_), C const& cond, T const& t, I0 const& i0, I1 const& i1 ) noexcept
  {
    return mask_op(cond, eve::bit_swap_pairs, t, i0, i1);
  }

  template<unsigned_value T, auto I0, auto I1>
  EVE_FORCEINLINE T
  bit_swap_pairs_(EVE_SUPPORTS(cpu_), T x
                 , std::integral_constant<size_t, I0> const & i0
                 , std::integral_constant<size_t, I1> const & i1) noexcept
  {
    constexpr auto S =  sizeof(element_type_t<T>)*8;
    if constexpr(I0 >= S)
    {
      if constexpr(I1 >= S) return x;
      else return  bit_unset(x, I1);
    }
    else if constexpr(I1 >= S) return  bit_unset(x, I0);
    else return bit_swap_pairs(x, I0, I1);
  }

  // Masked case
  template<conditional_expr C, unsigned_value T, auto I0, auto I1>
  EVE_FORCEINLINE auto
  bit_swap_pairs_(EVE_SUPPORTS(cpu_), C const& cond, T const& t
                 , std::integral_constant<size_t, I0> const & i0
                 , std::integral_constant<size_t, I1> const & i1) noexcept
  {
    return mask_op(cond, eve::bit_swap_pairs, t, i0, i1);
  }
}
