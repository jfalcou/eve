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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(iota_, iota);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto iota_(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept
    {
      if constexpr( scalar_value<T> )
      {
        return T(0);
      }
      else
      {
        return T([](auto i, auto ) { return i; } );
      }
    }
  }
}
