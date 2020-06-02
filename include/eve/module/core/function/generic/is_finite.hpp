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
#include <eve/function/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_finite_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(is_logical_v<T>)       return True(as(a));
      else if constexpr(scalar_value<T>)  return is_eqz(T(a-a));
      else                                return is_eqz(a-a);
    }
    else                            return apply_over(is_finite, a);
  }
}

