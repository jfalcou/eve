//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <eve/as.hpp>
#include <eve/traits.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <bit>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{
  template<unsigned_value T>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(cpu_)
                                , T x) noexcept
  {
    using r_t = as_integer_t<T, unsigned>;
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return r_t(std::popcount(x));
      }
      else
      {
//        return map(eve::popcount, v);
        constexpr auto siz = sizeof(eve::element_type_t<T>)*8;
        if constexpr(siz == 8)
        {
          x -= ((x >> 1) & T(0x55));
          x = ((x >> 2) & T(0x33)) + (x & T(0x33));
          return ((x + (x >> 4)) & T(0xF));
        }
        else if constexpr(siz <= 16)
        {
          x -= ((x >> 1) & T(0x5555));
          x = ((x >> 2) & T(0x3333)) + (x & T(0x3333));
          return ((((x + (x >> 4)) & T(0xF0F)) * T(0x101)) >> 8);
        }
        else if constexpr(siz == 32)
        {
          x -= ((x >> 1) & T(0x55555555));
          x = ((x >> 2) & T(0x33333333)) + (x & T(0x33333333));
          return ((((x + (x >> 4)) & T(0xF0F0F0F)) * T(0x1010101)) >> 24);
        }
        else if constexpr(siz == 64)
        {
          x -= (x >> 1) & T(0x5555555555555555ULL);
          x = ((x >> 2) & T(0x3333333333333333ULL)) + (x & T(0x3333333333333333ULL));
          return ((((x + (x >> 4)) & T(0xF0F0F0F0F0F0F0FULL)) * T(0x101010101010101ULL)) >> 56);
        }
      }
    }
    else
    {
      return apply_over(popcount, x);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_value  U>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, eve::popcount, t);
  }
}
