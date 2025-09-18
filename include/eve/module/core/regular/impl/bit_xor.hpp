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
      // T sclar, U simd, in this case we know that sizeof(T) == sizeof(U::value_type)
      return bit_xor(bit_cast(b, as<wide<T, cardinal_t<U>>>{}), a);
    }
    else
    {
      // both scalar, maybe floating, roundtrip to integer
      using i_t = as_integer_t<T, unsigned>;
      return bit_cast(static_cast<i_t>(bit_cast(a, as<i_t>{}) ^ bit_cast(b, as<i_t>{})), as(a));
    }
  }

  //================================================================================================
  // N parameters
  //================================================================================================
  template<typename T0, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto bit_xor_(EVE_REQUIRES(cpu_), O const &, T0 a0, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, Ts...>;
    if constexpr(sizeof...(Ts) == 0)
      return r_t(a0);
    else if constexpr(scalar_value<r_t> && (sizeof...(Ts)+1 >= eve::expected_cardinal_v<r_t>))
    {
      auto head = eve::as_wides(eve::zero(eve::as<r_t>()), a0, args...);
      auto s = eve::bit_xor(head);
      return butterfly_reduction(s, eve::bit_xor).get(0);
    }
    else
    {
      auto that = r_t(a0);
      ((that = bit_xor(that, r_t(args))), ...);
      return that;
    }
  }
}
