//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/oneminus.hpp>
#include <eve/module/core/regular/next.hpp>

namespace eve::detail
{

  template<typename T, floating_value U, callable_options O>
  EVE_FORCEINLINE constexpr T
  floor_(EVE_REQUIRES(cpu_), O const&, T const& a0, U const & eps) noexcept
  //  requires (O::contains(tolerant2))
  {
    // Hagerty's FL5 function
    auto q    = if_else(is_ltz(a0), one, oneminus(eps));
    auto rmax = q / (T(2) - eps);
    auto eps5 = eps / q;
    auto r    = floor(a0 + eve::max(eps, min(rmax, eps5 * eve::abs(inc(floor(a0))))));
    return if_else(is_lez(a0) || (r - a0 < rmax), r, dec(r));
  }

  template<typename T, integral_value U, callable_options O>
  EVE_FORCEINLINE constexpr T
  floor_(EVE_REQUIRES(cpu_), O const&, T const& a0, U const & e) noexcept
  //  requires (O::contains(tolerant2))
  {
    return floor(next(a0, e));
  }

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  floor_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
  {
    if constexpr(O::contains(tolerant2))
    {
      return floor[tolerant2](a0, 3*eps(as(a0)));
    }
    else
    {
      T z = eve::trunc(a0);
      return dec[z > a0](z);
    }
  }

  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr auto
  floor_(EVE_REQUIRES(cpu_), O const&, T const& a0, as<U> const & ) noexcept
  {
    auto z = floor(a0);
    if constexpr(unsigned_value<U>)
      return uint_(z);
    else if constexpr(signed_integral_value<U>)
      return int_(z);
    else
      return z;
  }

}
