//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(true__, true_);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto true__(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
       return as_logical_t<T>(true);
    }
  }
}
