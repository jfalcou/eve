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
#include <eve/module/core/regular/load.hpp>
#include <eve/module/core/regular/store.hpp>
#include <bit>


namespace eve::detail
{
  template<auto N, integral_value T>
  EVE_FORCEINLINE auto
  bit_swap_(EVE_SUPPORTS(cpu_), T x, std::integral_constant<size_t, N>) noexcept
  {
    using e_t =  element_type_t<T>;
    constexpr auto S = sizeof(e_t);
    auto  mk_ct = [S](uint8_t C){
      e_t r = C;
//      std::cout << std::hex << "mk_ct C = " << +r << std::endl;
      size_t shift = 4;
      constexpr size_t ls = S/2-(S == 8);
//      std::cout << "ls " << ls << std::endl;
      for(size_t i = 1; i <= ls; ++i)
      {
        shift *= 2;
//        std::cout << std::dec << "i =  " << i << ",  r = " << std::hex << +r << ",  shift = "<< std::dec << shift << std::endl;
        r += r << shift;
      }
//      std::cout << std::endl << std::hex << "mk_ct r = 0x" << +r << std::endl;
      return r;
    };
    if constexpr (N > S*4) return e_t(0);
    else if constexpr(N == 0) return x;
    else if constexpr(N == 1) //Return x with neighbor bits swapped.
    {
      e_t m = mk_ct(0x55);
      x =  ((x & m) << 1) | ((x & (bit_not(m))) >> 1);
    }
    else if constexpr(N == 2)//Return x with group of 2 bits swapped.
    {
      e_t m = mk_ct(0x33);
      x =  ((x & m) << 2) | ((x & (bit_not(m))) >> 2);
    }
    else if constexpr(N == 4)//Return x with group of 4 bits swapped.
    {
      e_t m = mk_ct(0x0f);
//      std::cout << "N = " << N << " ->" << std::hex << m << std::endl;
      x =  ((x & m) << 4) | ((x & (bit_not(m))) >> 4);
    }
    else if constexpr(N == 8)//Return x with group of 8 bits swapped.
    {
      e_t m = mk_ct(0xff);
      x =  ((x & m) << 8) | ((x & (bit_not(m))) >> 8);
    }
    else if constexpr(N == 16)//Return x with group of 16 bits swapped.
    {
      if constexpr(S == 8)
      {
        e_t m = 0x0000ffff0000ffffULL;
        x =  ((x & m) << 8) | ((x & (bit_not(m))) >> 8);
      }
      else // S = 4
        return  (x << 16) | (x >> 16);
    }
    else if constexpr(N == 32)//Return x with group of 32 bits swapped. (S = 8)
    {
      return (x << 32) | (x << 32);
    }
    return x;
  }

//   // Masked case
//   template<conditional_expr C, ordered_value U>
//   EVE_FORCEINLINE auto
//   bit_swap_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
//   {
//     return mask_op(cond, eve::bit_swap, t);
//   }
}
