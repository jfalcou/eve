//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(zero_, zero);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto zero_(EVE_SUPPORTS(cpu_), eve::as<T> const &) noexcept
    {
      return T(0);
    }
  }
}
