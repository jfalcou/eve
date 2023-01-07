//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<floating_scalar_value Type> struct complex;

  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE auto log10_(EVE_SUPPORTS(cpu_),
                                         cmplx_type const &,
                                         V v) noexcept
    {
      using c_t = as_complex_t<decltype(v)>;
      return c_t{log10(abs(v)), arg(v)/log_10(as(v))};
    }
  }
}
