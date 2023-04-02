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
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/byte_reverse.hpp>
#include <eve/module/core/regular/bit_swap_adjacent.hpp>
#include <eve/module/core/regular/bit_swap_pairs.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/dec.hpp>

namespace eve::detail
{
  template<unsigned_value T>
  EVE_FORCEINLINE auto
  bit_reverse_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using e_t =  element_type_t<T>;
    constexpr auto S = sizeof(e_t);
    if constexpr(scalar_value<T>)
    {
      x = bit_swap_adjacent(x, 1);
      x = bit_swap_adjacent(x, 2);
      x = bit_swap_adjacent(x, 4);
      if constexpr(sizeof(T) >= 2)
        x = bit_swap_adjacent(x, 8);
      else
        return x;
      if constexpr(sizeof(T) >= 4)
        x = bit_swap_adjacent(x, 16);
      else
        return x;
      if constexpr(sizeof(T) ==  8)
        x = bit_swap_adjacent(x, 32);
      return x;
    }
    else if constexpr(has_native_abi_v<T>)
    {
      if constexpr(S == 1)
      {
        x =  bit_shl((x & uint8_t(0x55)), 1) | bit_shr((x & uint8_t(0xaa)), 1);
        x =  bit_shl((x & uint8_t(0x33)), 2) | bit_shr((x & uint8_t(0xcc)), 2);
        x =  (bit_shl(x, 4) | bit_shr(x, 4));
        return x;
      }
      else
      {
        using u8_t = wide<uint8_t, fixed<S*cardinal_v<T>>>;
        auto z = eve::bit_cast(x, as<u8_t>());
        return byte_reverse( bit_cast(bit_reverse(z), as<T>()));
      }
    }
    else
      return apply_over(bit_reverse, x);
  }


  template<unsigned_value T,  integral_scalar_value N>
  EVE_FORCEINLINE T
  bit_reverse_(EVE_SUPPORTS(cpu_), T x, N n) noexcept
  {
    using e_t =  element_type_t<T>;
    constexpr size_t S = sizeof(e_t)*8;
    if (n == 0)         return x;
    else
    {
      auto y =  bit_reverse(x);
      if (2*n >= S)     return y;
      else if (n == 1u) return bit_swap_pairs(x, 0u, S-1u);
      else
      {
        constexpr auto o = e_t(1);
        e_t mask0 = (e_t(e_t(o << n)-o) << (S-n));
        auto mask =  bit_or(mask0, bit_reverse(mask0));
        return bit_or( bit_and(y, mask), bit_andnot(x, mask));
      }
    }
  }

  // Masked case
  template<conditional_expr C, unsigned_value U>
  EVE_FORCEINLINE auto
  bit_reverse_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::bit_reverse, t);
  }

  template<conditional_expr C, unsigned_value U,  integral_scalar_value N>
  EVE_FORCEINLINE auto
  bit_reverse_(EVE_SUPPORTS(cpu_), C const& cond
              , U const& t
              , N n) noexcept
  {
    return mask_op(cond, eve::bit_reverse, t, n);
  }
}
