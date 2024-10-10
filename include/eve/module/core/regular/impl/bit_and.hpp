//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr bit_value_t<T, U> bit_and_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
  {
    if constexpr (simd_value<T>)
    {
      // assume T != U
      if constexpr (simd_value<U>) return bit_and(a, bit_cast(b, as<T>{}));
      else                         return bit_and(a, T{ bit_cast(b, as<element_type_t<T>>{}) });
    }
    else if constexpr (simd_value<U>)
    {
      // T sclar, U simd, in this case we know that sizeof(T) == sizeof(U::value_type)
      return bit_and(bit_cast(b, as<wide<T, cardinal_t<U>>>{}), a);
    }
    else
    {
      // both scalar, maybe floating, roundtrip to integer
      using i_t = as_integer_t<T, unsigned>;
      return bit_cast(static_cast<i_t>(bit_cast(a, as<i_t>{}) & bit_cast(b, as<i_t>{})), as{a});
    }
  }

  //================================================================================================
  // N parameters
  //================================================================================================
  template<callable_options O, typename T0, typename T1, typename... Ts>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...> bit_and_(EVE_REQUIRES(cpu_), O const&, T0 a, T1 b, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;
    auto that = bit_and(r_t(a), r_t(b));
    ((that = bit_and(that, r_t(args))), ...);
    return that;
  }
}
