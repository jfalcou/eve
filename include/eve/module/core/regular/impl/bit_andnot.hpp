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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/traits/as_wides.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr bit_value_t<T, U> bit_andnot_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
  {
    if constexpr (simd_value<T>)
    {
      if constexpr (simd_value<U>)
      {
        if constexpr (std::same_as<T, U>) return map(bit_andnot, a, b);
        else                              return bit_andnot(a, inner_bit_cast(b, as<T>{}));
      }
      else                                return bit_andnot(a, T{ bit_cast(b, as<element_type_t<T>>{}) });
    }
    else if constexpr (simd_value<U>)
    {
      return bit_andnot(bit_cast(b, as<wide<T, cardinal_t<U>>>{}), a);
    }
    else
    {
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
    return bit_andnot(a, bit_or(b, args...));
  }
}
