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
  EVE_MAKE_CALLABLE(is_equal_, is_equal);

  namespace detail
  {
    template<value T, value U>
    EVE_FORCEINLINE   auto is_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
                  ->  decltype(as_logical_t<T>(a == b))
    {
      return as_logical_t<T>(a == b);
    }
  }
}
