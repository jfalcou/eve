//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_less_(EVE_REQUIRES(cpu_), O const& o, T a, T b) noexcept
  {
    if constexpr (O::contains(definitely))
    {
      static_assert(floating_value<T>, "[eve::is_less] The definitely option is only supported for floating types.");

      auto tol = o[definitely].value(T{});

      if constexpr (integral_value<decltype(tol)>) return a < eve::prev(b, tol);
      else                                         return a < fam(b, -tol, eve::max(eve::abs(a), eve::abs(b)));
    }
    else if constexpr (product_type<T>)
    {
      return kumi::to_tuple(a) < kumi::to_tuple(b);
    }
    else
    {
      if constexpr (scalar_value<T>) return as_logical_t<T>(a < b);
      else                           return map([](auto e, auto f) { return e < f; }, a, b);
    }
  }
}
