//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/fam.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve::detail
{
  template<callable_options O, value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_greater_(EVE_REQUIRES(cpu_), O const & o, T a, T b) noexcept
  {
    if constexpr(O::contains(definitely))
    {
      auto tol = o[definitely].value(T{});
      if constexpr(integral_value<decltype(tol)>) return a > eve::next(b, tol);
      else                                        return a > fam(b, tol, eve::max(eve::abs(a), eve::abs(b)));
    }
    else
    {
      return is_less(b, a);
    }
  }
}
