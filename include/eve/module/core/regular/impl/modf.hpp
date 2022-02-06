//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve::detail
{
  template<real_value T> EVE_FORCEINLINE constexpr
  kumi::tuple<T,T > modf_(EVE_SUPPORTS(cpu_), T a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( floating_real_value<T> )
      {
        auto t = trunc(a);
        return {a - t, t};
      }
      else
      {
        return {zero(eve::as(a)), a};
      }
    }
    else
    {
      return apply_over2(modf, a);
    }
  }
}
