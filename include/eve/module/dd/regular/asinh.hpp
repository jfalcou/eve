//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{

  namespace detail
  {
    template<floating_value V> EVE_FORCEINLINE V asinh_(EVE_SUPPORTS(cpu_)
                                                       , cmplx_type const &
                                                       , V const & v) noexcept
    {
      using r_t = eve::as_complex_t<V>;
      return if_else(eve::abs(v) <= 1, r_t(0, asin(v)), r_t(asinh(v)));
    }
  }
}
