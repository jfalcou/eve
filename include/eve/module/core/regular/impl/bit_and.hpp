//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/as_wides.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/simd_cast.hpp>
#include <eve/module/core/constant/allbits.hpp>

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
      // T scalar, U simd, in this case we know that sizeof(T) == sizeof(U::value_type)
      return bit_and(bit_cast(b, as<wide<T, cardinal_t<U>>>{}), a);
    }
    else
    {
      // both scalar, maybe floating, roundtrip to integer
      using i_t = as_integer_t<T, unsigned>;
      return bit_cast(static_cast<i_t>(bit_cast(a, as<i_t>{}) & bit_cast(b, as<i_t>{})), as(a));
    }
  }

  //================================================================================================
  // N parameters
  //================================================================================================
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
  bit_and_(EVE_REQUIRES(cpu_), O const&, T0 a0, T1 a1, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;

    if constexpr(scalar_value<r_t> && (sizeof...(Ts)+2 >= eve::expected_cardinal_v<r_t>))
    {
      auto head = eve::as_wides(eve::allbits(as<r_t>{}),
                                bit_cast(a0, as<r_t>{}),
                                bit_cast(a1, as<r_t>{}),
                                bit_cast(args, as<r_t>{})...);

      auto s = eve::bit_and(head);
      return butterfly_reduction(s, eve::bit_and).get(0);
    }
    else
    {
      auto that = bit_and(a0, a1);
      ((that = bit_and(that, args)), ...);
      return that;
    }
  }
}
