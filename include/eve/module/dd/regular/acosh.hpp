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
    template<floating_value V> EVE_FORCEINLINE V acosh_(EVE_SUPPORTS(cpu_)
                                                       , cmplx_type const &
                                                       , V const & v) noexcept
    {
      using r_t = eve::as_complex_t<V>;
      return if_else(eve::abs(v) <= 1, r_t(0, acos(v)), r_t(acosh(v)));
    }
    template<typename V> EVE_FORCEINLINE V acosh_(EVE_SUPPORTS(cpu_), V const & a0) noexcept
    {
      // acosh(a0) = +/-i acos(a0)
      // Choosing the sign of multiplier to give nt2::real(acosh(a0)) >= 0
      // we have compatibility with C99.
      auto res = eve::acos(a0);
      return if_else(is_lez(imag(res)),  mul_i(res), mul_mi(res));
  }
}
}
