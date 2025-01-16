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
        if      constexpr (scalar_value<U>)                    return common_logical_t<T, U>(a < b);
        else if constexpr (std::same_as<T, element_type_t<U>>) return is_less(U{a}, b);
        else                                                   return is_less(element_type_t<U>{a}, b);
      }
      else
      {
        if      constexpr (simd_value<U>)                      return map(is_less, a, b);
        else if constexpr (std::same_as<element_type_t<T>, U>) return is_less(a, T{b});
        else                                                   return is_less(a, element_type_t<T>{b});
      }
    }
  }
}
