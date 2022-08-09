//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/max.hpp>

namespace eve::detail
{
template<real_value T, decorator D>
EVE_FORCEINLINE constexpr T
rec_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  return rec(a0);
}

template<real_value T>
EVE_FORCEINLINE constexpr T
rec_(EVE_SUPPORTS(cpu_), T a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_real_value<T> ) { return T {1} / a; }
    else if( integral_value<T> )
    {
      if constexpr( scalar_value<T> )
      {
        // Generates a branch-less rec by triggering the use of conditional moves
        if( std::is_unsigned_v<T> )
        {
          auto b = a > 1 ? 0 : 1;
          return (a ? 1 : valmax(eve::as(a))) * b;
        }
        else
        {
          auto b1 = a > 1 ? 0 : 1;
          auto b2 = a < -1 ? 0 : 1;
          b2 *= b1;

          return (a ? a : valmax(eve::as(a))) * b2;
        }
      }
      else
      {
        if( std::is_unsigned_v<T> )
        {
          return if_else(
              is_eqz(a), valmax(eve::as(a)), if_else(eve::abs(a) == one(eve::as(a)), a, eve::zero));
        }
        else { return map(eve::rec, a); }
      }
    }
  }
  else { return apply_over(rec, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
rec_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::rec, t);
}
}
