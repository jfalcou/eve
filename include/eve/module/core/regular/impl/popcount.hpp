//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/spy.hpp>
#include <eve/traits.hpp>
#include <bit>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto popcount_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
  {
    if constexpr( scalar_value<T> )
      return T(std::popcount(x));
    else
    {
      constexpr auto siz = sizeof(eve::element_type_t<T>) * 8;
      if constexpr( siz == 8 )
      {
        x -= ((x >> 1) & T(0x55));
        x = ((x >> 2) & T(0x33)) + (x & T(0x33));
        return ((x + (x >> 4)) & T(0xF));
      }
      else if constexpr( siz <= 16 )
      {
        x -= ((x >> 1) & T(0x5555));
        x = ((x >> 2) & T(0x3333)) + (x & T(0x3333));
        return ((((x + (x >> 4)) & T(0xF0F)) * T(0x101)) >> 8);
      }
      else if constexpr( siz == 32 )
      {
        x -= ((x >> 1) & T(0x55555555));
        x = ((x >> 2) & T(0x33333333)) + (x & T(0x33333333));
        return ((((x + (x >> 4)) & T(0xF0F0F0F)) * T(0x1010101)) >> 24);
      }
      else if constexpr( siz == 64 )
      {
        x -= (x >> 1) & T(0x5555555555555555ULL);
        x = ((x >> 2) & T(0x3333333333333333ULL)) + (x & T(0x3333333333333333ULL));
        return ((((x + (x >> 4)) & T(0xF0F0F0F0F0F0F0FULL)) * T(0x101010101010101ULL)) >> 56);
      }
    }
  }
}
