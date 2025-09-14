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
#include <eve/module/core/constant/minorant.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_ordered.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/traits/as_wides.hpp>

namespace eve::detail
{
  template<typename T0, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto max_(EVE_REQUIRES(cpu_), O const & o, T0 aa0, Ts... as) noexcept
  {
    using r_t = eve::common_value_t<T0, Ts...>;
    if constexpr(sizeof...(Ts) == 1) // 2 parameters
    {
      r_t a0(aa0);
      r_t a1(as...);
      if constexpr(O::contains(pedantic)) //pedantic
      {
        if      constexpr( integral_value<r_t> ) return eve::max(a0, a1);
        else if constexpr( eve::platform::supports_invalids )
        {
          if constexpr(scalar_value<r_t>)
          {
            if( is_eqz(a0) && is_eqz(a1) ) return bit_and(a0, a1);
            return is_unordered(a0, a1) ? a0 : eve::max(a0, a1);
          }
          else
          {
            auto tmp = eve::max[is_ordered(a0, a1)](a0, a1);
            return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), tmp);
          }
        }
        else
        {
          if constexpr(scalar_value<r_t>)
          {
            return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
          }
          else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
        }
      }
      else if  constexpr(O::contains(numeric))  // numeric
      {
        if      constexpr( integral_value<r_t> )  return max(a0, a1);
        else if constexpr( eve::platform::supports_invalids )
        {
          if constexpr(scalar_value<r_t>)
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
          if constexpr(scalar_value<r_t>)
          {
            return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
          }
          else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
        }
      }
      else
      {
        if constexpr(scalar_value<r_t>) return a0 < a1 ? a1 : a0;
        else                          return if_else(a0 < a1, a1, a0);
      }
    }
    else // N > 2 parameters
    {
      if constexpr(scalar_value<r_t> && (sizeof...(Ts)+1 >= eve::expected_cardinal_v<r_t>))
      {
        auto head = eve::as_wides(eve::minorant(eve::as<r_t>()), aa0, as...);
        auto s = eve::max[o](head);
        return butterfly_reduction(s, eve::max);
      }
      else
      {
        auto m = max[o];
        r_t that(aa0);
        ((that = m(that, as)), ...);
        return that;
      }
    }
  }
  //================================================================================================
  // Predicate case
  //================================================================================================
  template<typename Callable>
  EVE_FORCEINLINE constexpr auto
  build_max_callable(Callable const & f) noexcept
  {
    if      constexpr( std::same_as<Callable, eve::is_less_t<eve::options<>>>     ) return eve::max;
    else if constexpr( std::same_as<Callable, eve::is_greater_t<eve::options<>>>  ) return eve::min;
    else
    {
      return [f](auto x, auto y){ return eve::if_else(f(y, x), x, y); };
    };
  }
}
