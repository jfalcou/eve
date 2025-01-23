//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/as_arithmetic.hpp>

#include <concepts>

namespace eve
{
  template<typename T>
  struct as_logical;
}

namespace eve::detail
{
  template <logical_value A, logical_value B>
  inline consteval auto logical_tie_breaker_impl()
  {
    using ea_t = as_arithmetic_t<element_type_t<A>>;
    using eb_t = as_arithmetic_t<element_type_t<B>>;

    if constexpr (std::same_as<ea_t, eb_t>)
    {
      return A{};
    }
    // smallest type
    else if constexpr (sizeof(ea_t) != sizeof(eb_t))
    {
      if constexpr (sizeof(ea_t) < sizeof(eb_t)) return A{};
      else                                       return B{};
    }
    // unsigned first
    else if constexpr (signed_value<ea_t> != signed_value<eb_t>)
    {
      if constexpr (signed_value<ea_t>)          return B{};
      else                                       return A{};
    }
    // integral first
    else if constexpr (integral_value<ea_t> != integral_value<eb_t>)
    {
      if constexpr (integral_value<ea_t>)        return A{};
      else                                       return B{};
    }
    // both types have the same size, signedness and integral-ness, they are functionally the same.
    else
    {
      // handles the (long, long long) and (unsigned long, unsigned long long) cases
      if constexpr (std::same_as<decltype(ea_t{} + eb_t{}), ea_t>) return A{};
      else                                                         return B{};
    }
  }

  template<typename A, typename B, typename... Ts>
  struct logical_tie_breaker
  {
    using type = typename logical_tie_breaker<typename logical_tie_breaker<A, B>::type, Ts...>::type;
  };

  template <typename A, typename B>
  struct logical_tie_breaker<A, B>
  {
    using type = decltype(logical_tie_breaker_impl<typename as_logical<A>::type, typename as_logical<B>::type>());
  };

  template<typename A, typename B>
  using logical_tie_breaker_t = typename logical_tie_breaker<A, B>::type;
}
