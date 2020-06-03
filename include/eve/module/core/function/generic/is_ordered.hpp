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
#include <eve/function/is_equal.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/constant/true.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_ordered_(EVE_SUPPORTS(cpu_)
                                                       , T const &a
                                                       , T const &b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return True(as(a));
      else                            return (a == a) && (b == b);
    }
    else                              return apply_over(is_ordered, a, b);
  }
}

