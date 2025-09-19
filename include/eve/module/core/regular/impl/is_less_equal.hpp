//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/fam.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_less_equal_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
  {
    if constexpr (O::contains(almost))
    {
      auto tol = o[almost].value(as(a));
      if constexpr(integral_value<decltype(tol)>) return a <=  eve::next(b, tol);
      else                                        return a <= fam(b, tol, eve::max(eve::abs(a), eve::abs(b)));
    }
    else if constexpr (product_type<T>)
    {
      return kumi::to_tuple(a) <= kumi::to_tuple(b);
    }
    else
    {
      if constexpr (scalar_value<T>) return as_logical_t<T>(a <= b);
      else                           return map([]<typename E>(E e, E f){ return as_logical_t<E>(e <= f); }, a, b);
    }
  }
}
