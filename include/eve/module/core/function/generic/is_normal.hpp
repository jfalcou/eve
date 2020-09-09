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
#include <eve/function/abs.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_normal_(EVE_SUPPORTS(cpu_)
                                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return is_nez(a);
      else                            return is_finite(a) && is_greater_equal(eve::abs(a), Smallestposval(eve::as(a)));
    }
    else                              return apply_over(is_normal, a);
  }
}

