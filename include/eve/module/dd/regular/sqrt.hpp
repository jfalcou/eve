//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/complex/regular/traits.hpp>

namespace eve
{

  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE auto sqrt_( EVE_SUPPORTS(cpu_)
                              , cmplx_type const &
                              , V const & v) noexcept
    {
      using c_t = as_complex_t<V>;
      return if_else(is_positive(v), c_t{sqrt(v), zero(as(v))}, c_t{zero(as(v)), sqrt(-v)});
    }
  }
}
