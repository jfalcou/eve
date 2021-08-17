//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(mone_, mone);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto mone_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return T(-1);
    }
  }
}
