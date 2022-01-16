//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp
#include <eve/module/arithmetic.hpp>
#include <eve/module/polynomial/regular/hermite.hpp>

namespace eve::detail
{

  template<integral_value N, floating_real_value T>
  EVE_FORCEINLINE constexpr auto hermite_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  requires index_compatible_values<N, T>
  {
    return fma(x+x, hermite(n, x), -hermite(inc(n), x));
  }
}
