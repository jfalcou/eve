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
#include <eve/module/core/regular/prev.hpp>

namespace eve::detail
{

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  ceil_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
  {
    if constexpr(O::contains(almost))
    {
      auto tol = o[almost].value(as(a0));
      if constexpr(integral_value<decltype(tol)>)
        return ceil(prev(a0, tol));
      else
        return -floor[o](-a0);
    }
    else
      return -floor(-a0);
  }


  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr auto
  ceil_(EVE_REQUIRES(cpu_), O const&, T const& a0, as<U> const & ) noexcept
  {
    if constexpr(integral_value<T>)
      return convert(a0, as_element<as_integer_t<T,U>>{});
    else
      return convert(ceil(a0), as_element<as_integer_t<T,U>>{});
  }
}
