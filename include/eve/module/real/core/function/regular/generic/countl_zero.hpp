//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/gather.hpp>
#include <eve/function/is_nez.hpp>

#include <bit>
#include <type_traits>

namespace eve::detail
{
  template<unsigned_value T> EVE_FORCEINLINE T countl_zero_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return T(std::countl_zero(x));
    }
    else if constexpr( has_native_abi_v<T> )
    {
      std::cout << "ici" << std::endl; 
//      return map(countl_zero, v); // TO DO
      constexpr auto siz = sizeof(eve::element_type_t<T>)*8;
      using elt_t = element_type_t<T>;
      constexpr elt_t vals[16] = {4,3,2,2,1,1,1,1,0,0,0,0,0,0,0,0};
      if constexpr(siz <= 8)
      {
        T zeroes(4);
        auto t = is_nez(x >> 4);
        zeroes  -= if_else(t, T(4), zero);
        x      >>= if_else(t, T(4), zero);
        return gather(&vals[0],x) + zeroes;
      }
      else if constexpr(siz <= 16)
      {
        T zeroes(12);
        auto t = is_nez(x >> 8);
        zeroes  -= if_else(t, T(8), zero);
        x      >>= if_else(t, T(8), zero);
        t = is_nez(x >> 4);
        zeroes  -= if_else(t, T(4), zero);
        x      >>= if_else(t, T(4), zero);
        return gather(&vals[0],x) + zeroes;
      }
      else if constexpr(siz == 32)
      {
        T zeroes(28);
        auto t = is_nez(x >> 16);
        zeroes  -= if_else(t, T(16), zero);
        x      >>= if_else(t, T(16), zero);
        t = is_nez(x >> 8);
        zeroes  -= if_else(t, T(8), zero);
        x      >>= if_else(t, T(8), zero);
        t = is_nez(x >> 4);
        zeroes  -= if_else(t, T(4), zero);
        x      >>= if_else(t, T(4), zero);
        return gather(&vals[0],x) + zeroes;
      }
      else if constexpr(siz == 64)
      {
        T zeroes(60);
        auto t = is_nez(x >> 32);
        zeroes  -= if_else(t, T(32), zero);
        x      >>= if_else(t, T(32), zero);
        t = is_nez(x >> 16);
        zeroes  -= if_else(t, T(16), zero);
        x      >>= if_else(t, T(16), zero);
        t = is_nez(x >> 8);
        zeroes  -= if_else(t, T(8), zero);
        x      >>= if_else(t, T(8), zero);
        t = is_nez(x >> 4);
        zeroes  -= if_else(t, T(4), zero);
        x      >>= if_else(t, T(4), zero);
        return gather(&vals[0],x) + zeroes;
      }
    }
    else
      return apply_over(countl_zero, x);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_value U>
  EVE_FORCEINLINE auto countl_zero_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, countl_zero, t);
  }
}
