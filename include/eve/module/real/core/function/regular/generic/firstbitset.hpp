//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/inc.hpp>
#include <eve/constant/one.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_real_value T>
  EVE_FORCEINLINE constexpr T firstbitset_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
   if constexpr(has_native_abi_v<T>)
    {
      return a0 & inc(~a0);
    }
    else return apply_over(firstbitset, a0);
  }

}
