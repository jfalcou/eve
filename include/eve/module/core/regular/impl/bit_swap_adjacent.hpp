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
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
  template<unsigned_value T, integral_scalar_value N>
  EVE_FORCEINLINE T
  bit_swap_adjacent_(EVE_SUPPORTS(cpu_), T x, N n) noexcept
  {
    EVE_ASSERT(eve::all(n >= 0),  "some n elements are less than 0");
    using e_t =  element_type_t<T>;
    constexpr auto S = sizeof(e_t);
    auto  mk_ct = [](uint8_t C){
      e_t r = C;
      size_t shift = 4;
      constexpr size_t ls = S/2-(S == 8);//logarithm
      for(size_t i = 1; i <= ls; ++i)
      {
        shift *= 2;
        r += r << shift;
      }
      return r;
    };
    auto swp = [](auto x, auto m, int n)->T{
      return bit_or(bit_shl(bit_and(x, T(m)), n), bit_shr(bit_andnot(x, T(m)), n));
    };
    if (n > S*4) return zero(as(x));
    else if (n == 0) return x;
    else if (n == 1) //Return x with neighbor bits swapped.
      return swp(x, mk_ct(0x55), n);
    else if (n == 2)//Return x with group of 2 bits swapped.
      return swp(x, mk_ct(0x33), n);
    else if (n == 4)//Return x with group of 4 bits swapped.
      return swp(x, mk_ct(0x0f), n);
    else if (n == 8)//Return x with group of 8 bits swapped.
    {
      if      constexpr(S == 2) return (x << n) | (x >> n);
      else if constexpr(S == 4) return swp(x, 0x00ff00ffU, n);
      else if constexpr(S == 8) return swp(x, 0x00ff00ff00ff00ffUL, n);
    }
    else if (n == 16) //Return x with group of 16 bits swapped.
    {
      if      constexpr(S == 4) return (x << n) | (x >> n);
      else if constexpr(S == 8) return swp(x, 0x0000ffff0000ffffUL, n);
    }
    else if (n == 32) //Return x with group of 32 bits swapped. (S = 8)
      return (x << n) | (x >> n);
  }

  // Masked case
  template<conditional_expr C, unsigned_value U, integral_value N>
  EVE_FORCEINLINE auto
  bit_swap_adjacent_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, N const & n) noexcept
  {
    return mask_op(cond, eve::bit_swap_adjacent, t, n);
  }
}
