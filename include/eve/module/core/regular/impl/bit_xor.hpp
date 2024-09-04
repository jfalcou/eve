//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/operators.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr bit_value_t<T, U> bit_xor_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
  {
    if constexpr (simd_value<T>)
    {
      // assume T != U
      if constexpr (simd_value<U>) return bit_xor(a, bit_cast(b, as<T>{}));
      else                         return bit_xor(a, T{ bit_cast(b, as<element_type_t<T>>{}) });
    }
    else if constexpr (simd_value<U>)
    {
      // T sclar, U simd
      return bit_xor(bit_cast(b, as<typename U::template rebind<T>>{}), a);
    }
    else
    {
      // both scalar
      return a ^ bit_cast(b, as<T>{});
    }
  }
  
  //================================================================================================
  // N parameters
  //================================================================================================
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
  bit_xor_(EVE_REQUIRES(cpu_), O const &, T0 a, T1 b, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;
    auto that = bit_xor(r_t(a), r_t(b));
    ((that = bit_xor(that, r_t(args))), ...);
    return that;
  }
}
