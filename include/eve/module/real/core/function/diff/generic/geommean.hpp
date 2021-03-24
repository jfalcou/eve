//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/half.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/diff/sqrt.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  template<auto N, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr T geommean_(EVE_SUPPORTS(cpu_)
                                       , diff_type<N> const &
                                       , T a,  U b) noexcept
  requires compatible_values<U, T>
  {
    if constexpr(N == 1)
      return diff(sqrt)(a)*sqrt(b);
    else if (N ==  2)
      return diff(sqrt)(b)*sqrt(a);
    else
      return common_compatible_t<T, U>(0);
  }

}
