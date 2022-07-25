//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto acosd_(EVE_SUPPORTS(cpu_), D const &decorator, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return radindeg(decorator(acos)(a));
    }
    else
    {
      return apply_over(decorator(acosd), a);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acosd_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return acosd(regular_type(), a);
  }
}
