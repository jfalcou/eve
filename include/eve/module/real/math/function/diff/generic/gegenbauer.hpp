//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/gegenbauer.hpp>
#include <eve/function/all.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_value N, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr T gegenbauer_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const &n
                                  , T const &l
                                  , U const &x) noexcept
  requires index_compatible_values<N, T> && compatible_values<T, U>
  {
    if (eve::all(n < one(as(n))))   return zero(as(x));
    return 2*l*gegenbauer(dec(n), inc(l), x);
  }
}
