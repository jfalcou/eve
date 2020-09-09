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
#include <eve/function/is_not_equal.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/constant/true.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <cmath>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_unordered_(EVE_SUPPORTS(cpu_)
                                                         , T const &a
                                                         , T const &b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_real_scalar_value<T>) return std::isunordered(a, b);
      if constexpr(integral_value<T>) return False(eve::as(a));
      else                            return (a != a) || (b != b);
    }
    else                              return apply_over(is_unordered, a, b);
  }
}

