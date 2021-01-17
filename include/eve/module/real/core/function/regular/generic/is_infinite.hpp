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
#include <eve/constant/false.hpp>
#include <eve/constant/inf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_infinite_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
          if constexpr(integral_value<T>)   return false_(eve::as(a));
    else  if constexpr(has_native_abi_v<T>) return is_equal(eve::abs(a), inf(eve::as(a)));
    else                                    return apply_over(is_infinite, a);
  }
}
