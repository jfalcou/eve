//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_not.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr bit_value_t<T, U> bit_andnot_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
  {
    if constexpr (simd_value<T>)
    {
      if constexpr (simd_value<U>)
      {
        if constexpr (std::same_as<T, U>) return bit_and(bit_not(a), b);
        else                              return bit_andnot(a, bit_cast(b, as<T>{}));
      }
      else                                return bit_andnot(a, T{ bit_cast(b, as<element_type_t<T>>{}) });
    }
    else if constexpr (simd_value<U>)
    {
      // T scalar, U simd, in this case we know that sizeof(T) == sizeof(U::value_type)
      return bit_andnot(bit_value_t<T, U>{ a }, bit_cast(b, as<bit_value_t<T, U>>{}));
    }
    else
    {
      // both scalar, maybe floating, roundtrip to integer
      using i_t = as_integer_t<T, unsigned>;
      return bit_cast(static_cast<i_t>(bit_cast(a, as<i_t>{}) & ~bit_cast(b, as<i_t>{})), as(a));
    }
  }

  //================================================================================================
  // N parameters
  //================================================================================================
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  bit_andnot_(EVE_REQUIRES(cpu_), O const &, T0 a, T1 b, Ts... args) noexcept
  {
    return bit_andnot(a, bit_and(b, args...));
  }
}
