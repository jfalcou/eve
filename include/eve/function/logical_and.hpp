//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(logical_and_, logical_and);

  namespace detail
  {
    template<logical_value T, logical_value U>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a && b);
      else                                                return a && b;
    }

    template<logical_value T>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
    {
      return a && T{b};
    }

    template<logical_value U>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
    {
      return U{a} && b;
    }
  }
}
