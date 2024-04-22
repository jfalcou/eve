//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr T max_(EVE_REQUIRES(cpu_), O const & o, T a0, T a1, Ts... as) noexcept
  {
    if constexpr(sizeof...(Ts) == 0) // 2 parameters
    {
      if constexpr(O::contains(pedantic2)) //pedantic
      {
        if      constexpr( integral_value<T> ) return max(a0, a1);
        else if constexpr( eve::platform::supports_invalids )
        {
          if constexpr(scalar_value<T>)
          {
            if( is_eqz(a0) && is_eqz(a1) ) return bit_and(a0, a1);
            return is_unordered(a0, a1) ? a0 : eve::max(a0, a1);
          }
          else
          {
            auto tmp = if_else(is_unordered(a0, a1), a0, eve::max(a0, a1));
            return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), tmp);
          }
        }
        else
        {
          if constexpr(scalar_value<T>)
          {
            return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
          }
          else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
        }
      }
      else if  constexpr(O::contains(numeric))  // numeric
      {
        if      constexpr( integral_value<T> )  return max(a0, a1);
        else if constexpr( eve::platform::supports_invalids )
        {
          if constexpr(scalar_value<T>)
          {
            if( is_eqz(a0) && is_eqz(a1) ) return bit_and(a0, a1);
            return is_nan(a0) ? a1 : is_nan(a1) ? a0 : max(a0, a1);
          }
          else
          {
            auto tmp = if_else(is_nan(a0), a1, if_else(is_nan(a1), a0, max(a0, a1)));
            return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), tmp);
          }
        }
        else
        {
          if constexpr(scalar_value<T>)
          {
            return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
          }
          else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
        }
      }
      else
      {
        if constexpr(scalar_value<T>) return a0 < a1 ? a1 : a0;
        else                          return if_else(a0 < a1, a1, a0);
      }
    }
    else // N > 2 parameters
    {
      auto m = max[o];
      T that(m(a0, a1));
      ((that = m(that, as)), ...);
      return that;
    }
  }

  //================================================================================================
  // Predicate case
  //================================================================================================
  template<typename Callable, callable_options O>
  EVE_FORCEINLINE constexpr auto
  max_(EVE_REQUIRES(cpu_), O const &, Callable const & f) noexcept
  {
    if      constexpr( std::same_as<Callable, eve::callable_is_less_>    ) return eve::max;
    else if constexpr( std::same_as<Callable, eve::callable_is_greater_> ) return eve::min;
    else
    {
      return [f](auto x, auto y){ return eve::if_else(f(y, x), x, y); };
    };
  }
}
