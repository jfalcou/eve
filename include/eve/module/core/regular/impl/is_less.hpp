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
  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr common_logical_t<T, U> is_less_(EVE_REQUIRES(cpu_), O const& o, T a, U b) noexcept
  {
    if constexpr (product_type<T> && product_type<U>)
    {
      return convert(kumi::to_tuple(a) < kumi::to_tuple(b), as_element<common_logical_t<T, U>>());
    }
    else if constexpr (O::contains(definitely))
    {
      static_assert(floating_value<T> && floating_value<U>, "[EVE] eve::is_less[definitely] only accepts floating point values.");

      using w_t = common_value_t<T, U>;
      auto aa = w_t{a};
      auto bb = w_t{b};

      auto tol = o[definitely].value(w_t{});

      if constexpr (integral_value<decltype(tol)>) return aa < eve::prev(bb, tol);
      else                                         return aa < fam(bb, -tol, eve::max(eve::abs(aa), eve::abs(bb)));
    }
    else
    {
      if constexpr (scalar_value<T>)
      {
        if      constexpr (scalar_value<U>) return common_logical_t<T, U>(a < b);
        // because of the auto-conversion rules in elementwise_callable, we can assume that T will have the type
        // element_type<U> at that point and that the appropriate wide<S> x S backend doesn't exist.
        else                                return is_less(U{a}, b);
      }
      else
      {
        if      constexpr (simd_value<U>) return map(is_less, a, b);
        // because of the auto-conversion rules in elementwise_callable, we can assume that U will have the type
        // element_type<T> at that point and that the appropriate wide<S> x S backend doesn't exist.
        else                              return is_less(a, T{b});
      }
    }
  }
}
