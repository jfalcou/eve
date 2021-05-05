//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(logical_or_, logical_or);

  namespace detail
  {
    template<logical_value T, logical_value U>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a || b);
      else                                                return a || b;
    }

    template<logical_value T>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
    {
      return b ? true(as<T>()) : T{a};
    }

    template<logical_value U>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
    {
      return a ? true_(as<U>()) : U{b};
    }

    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
    {
      return a || b;
    }
  }
}
