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

namespace eve::detail
{
  template<auto N, unsigned_value T>
  EVE_FORCEINLINE T
  bit_swap_(EVE_SUPPORTS(cpu_), T x, std::integral_constant<size_t, N>) noexcept
  {
    using e_t =  element_type_t<T>;
    constexpr auto S = sizeof(e_t);
    auto  mk_ct = [](uint8_t C){
      e_t r = C;
      size_t shift = 4;
      constexpr size_t ls = S/2-(S == 8);
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
    if constexpr (N > S*4) return zero(as(x));
    else if constexpr(N == 0) return x;
    else if constexpr(N == 1) //Return x with neighbor bits swapped.
      return swp(x, mk_ct(0x55), N);
    else if constexpr(N == 2)//Return x with group of 2 bits swapped.
      return swp(x, mk_ct(0x33), N);
    else if constexpr(N == 4)//Return x with group of 4 bits swapped.
      return swp(x, mk_ct(0x0f), N);
    else if constexpr(N == 8)//Return x with group of 8 bits swapped.
    {
      if      constexpr(S == 2) return (x << N) | (x >> N);
      else if constexpr(S == 4) return swp(x, 0x00ff00ffU, N);
      else if constexpr(S == 8) return swp(x, 0x00ff00ff00ff00ffUL, N);
    }
    else if constexpr(N == 16)//Return x with group of 16 bits swapped.
    {
      if      constexpr(S == 4) return (x << N) | (x >> N);
      else if constexpr(S == 8) return swp(x, 0x0000ffff0000ffffUL, N);
    }
    else if constexpr(N == 32)//Return x with group of 32 bits swapped. (S = 8)
      return (x << N) | (x >> N);
  }

  // Masked case
  template<conditional_expr C, ordered_value U, auto N>
  EVE_FORCEINLINE auto
  bit_swap_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, std::integral_constant<size_t, N> const & n) noexcept
  {
    return mask_op(cond, eve::bit_swap, t, n);
  }
}
