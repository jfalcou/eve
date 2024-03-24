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

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
  bit_andnot_(EVE_REQUIRES(cpu_), O const &, T0 a, T1 b, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0)
    {
      if constexpr(scalar_value<r_t>)
      {
        if constexpr( floating_value<r_t> )
        {
          using b_t = as_integer_t<r_t>;
          return bit_cast(b_t(bit_cast(a, as<b_t>()) & ~bit_cast(b, as<b_t>())), as(a));
        }
        else return r_t(a & ~b);
      }
      else
      {
        using b_t = as_integer_t<r_t>;
        return bit_cast(b_t(bit_cast(a, as<b_t>()) & ~bit_cast(b, as<b_t>())), as(a));
      }
    }
    else
    {
      auto that = bit_andnot(r_t(a), r_t(b));
      ((that = bit_andnot(that, r_t(args))), ...);
      return that;
    }
  }
}
