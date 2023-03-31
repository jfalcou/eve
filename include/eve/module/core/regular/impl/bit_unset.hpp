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
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<unsigned_value T, unsigned_value I0>
  EVE_FORCEINLINE T
  bit_unset_(EVE_SUPPORTS(cpu_), T a, I0 i0) noexcept
  {
    constexpr size_t S8 = sizeof(element_type_t<T>)*8;
    EVE_ASSERT(i0 < S8, "indexis out or range");
    return bit_andnot(a, bit_shl(one(as(a)), i0));
  }

  // Masked case
  template<conditional_expr C, unsigned_value T, unsigned_value I0>
  EVE_FORCEINLINE auto
  bit_unset_(EVE_SUPPORTS(cpu_), C const& cond, T const& t, I0 const& i0) noexcept
  {
    return mask_op(cond, eve::bit_unset, t, i0);
  }

  template<unsigned_value T, auto I0>
  EVE_FORCEINLINE T
  bit_unset_(EVE_SUPPORTS(cpu_), T x
                 , std::integral_constant<size_t, I0> const & ) noexcept
  {
    constexpr auto S =  sizeof(element_type_t<T>)*8;
    if constexpr(I0 >= S) return x;
    else return bit_andnot(x, bit_shl(one(as(x)), I0));
  }

  // Masked case
  template<conditional_expr C, unsigned_value T, auto I0>
  EVE_FORCEINLINE auto
  bit_unset_(EVE_SUPPORTS(cpu_), C const& cond, T const& t
                 , std::integral_constant<size_t, I0> const & i0) noexcept
  {
    return mask_op(cond, eve::bit_unset, t, i0);
  }
}
