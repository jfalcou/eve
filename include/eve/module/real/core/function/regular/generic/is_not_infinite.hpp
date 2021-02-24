//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_infinite_(EVE_SUPPORTS(cpu_)
                                                       , T const &a) noexcept
  {
    return !eve::is_infinite(a);
  }
}

