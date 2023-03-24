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
#include <eve/module/core/regular/load.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/byte_reverse.hpp>
#include <eve/module/core/regular/rotl.hpp>
#include <bit>


namespace eve::detail
{
  template<auto N, integral_value T>
  EVE_FORCEINLINE auto
  bit_swap_(EVE_SUPPORTS(cpu_), T x, std::integral_constant<size_t, N>) noexcept;

  template<auto N, integral_value T>
  EVE_FORCEINLINE auto
  bit_swap_(EVE_SUPPORTS(cpu_), T x, std::integral_constant<size_t, N> n) noexcept
  {
    using e_t =  element_type_t<T>;
    if constexpr(std::is_signed_v<e_t>)
      return bit_cast(bit_swap(bit_cast(x, as<as_uinteger_t<T>>()), n), as<T>());
    constexpr auto S = sizeof(e_t);
    auto  mk_ct = [S](uint8_t C){
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
    if constexpr (N > S*4) return e_t(0);
    else if constexpr(N == 0) return x;
    else if constexpr(N == 1) //Return x with neighbor bits swapped.
    {
      e_t m = mk_ct(0x55);
      x =  ((x & m) << 1) | ((x & (bit_not(m))) >> 1);
      return x;
    }
    else if constexpr(N == 2)//Return x with group of 2 bits swapped.
    {
      e_t m = mk_ct(0x33);
      x =  ((x & m) << 2) | ((x & (bit_not(m))) >> 2);
      return x;
    }
    else if constexpr(N == 4)//Return x with group of 4 bits swapped.
    {
      e_t m = mk_ct(0x0f);
      x =  ((x & m) << 4) | ((x & (bit_not(m))) >> 4);
      return x;
    }
    else if constexpr(N == 8)//Return x with group of 8 bits swapped.
    {
      if constexpr( S == 2)
      {
        return rotl(x, 8);
      }
      else if constexpr( S == 4)
      {
        e_t m = 0x00ff00ffULL;
        x =  ((x & m) << 8) | ((x & (bit_not(m))) >> 8);
        return x;
      }
       else if constexpr( S == 8)
      {
        e_t m = 0x00ff00ff00ff00ffULL;
        x =  ((x & m) << 8) | ((x & (bit_not(m))) >> 8);
        return x;
      }
   }
    else if constexpr(N == 16)//Return x with group of 16 bits swapped.
    {
      if constexpr(S == 8)
      {
        e_t m = 0x0000ffff0000ffffULL;
        x =  ((x & m) << 16) | ((x & (bit_not(m))) >> 16);
        return x;
      }
      else if constexpr( S == 4)
        return  rotl(x, 16); ;
    }
    else if constexpr(N == 32)//Return x with group of 32 bits swapped. (S = 8)
    {
      return rotl(x, 32);
    }
  }

  // Masked case
  template<conditional_expr C, ordered_value U, size_t N>
  EVE_FORCEINLINE auto
  bit_swap_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, std::integral_constant<size_t, N> const & n) noexcept
  {
    return mask_op(cond, eve::bit_swap, t, n);
  }
}
