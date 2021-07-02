//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(one_, one);
  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto one_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return T(1);
    }
  }
}
