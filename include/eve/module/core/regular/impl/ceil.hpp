//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/floor.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  ceil_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
  {
    if constexpr(O::contains(tolerant2))
    {
      return ceil[tolerant2](a0, 3*eps(as(a0)));
    }
    else
    {
      T z = eve::trunc(a0);
      return inc[z < a0](z);
    }
  }

  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr auto
  ceil_(EVE_REQUIRES(cpu_), O const&, T const& a0, as<U> const & ) noexcept
  {
    auto z = ceil(a0);
    if constexpr(unsigned_value<U>)
      return uint_(z);
    else if constexpr(signed_integral_value<U>)
      return int_(z);
    else
      return z;
  }

  template<typename T, scalar_value U, callable_options O>
  EVE_FORCEINLINE constexpr T
  ceil_(EVE_REQUIRES(cpu_), O const&, T const& a0, U const & eps) noexcept
  requires (O::contains(tolerant2))
  {
    return -floor[tolerant2](-a0, eps);

  }

}
