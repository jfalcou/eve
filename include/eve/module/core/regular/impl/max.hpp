//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  max_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0) // 2 parameters
    {
      if constexpr( has_native_abi_v<T0> )
      {
        constexpr bool is_scalar = scalar_value<r_t>;
        auto a0 = r_t(r0);
        auto a1 = r_t(r1);

        if constexpr(O::contains(pedantic2)) //pedantic
        {
          if      constexpr( integral_value<r_t> ) return max(a0, a1);
          else if constexpr( eve::platform::supports_invalids )
          {
            if constexpr(is_scalar)
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
            if constexpr(is_scalar)
            {
              return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
            }
            else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
          }
        }
        else if  constexpr(O::contains(numeric2))  // numeric
        {
          if      constexpr( integral_value<r_t> )  return max(a0, a1);
          else if constexpr( eve::platform::supports_invalids )
          {
            if constexpr(is_scalar)
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
            if constexpr(is_scalar)
            {
              return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
            }
            else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
          }
        }
        else
        {
          if constexpr(is_scalar) return a0 < a1 ? a1 : a0;
          else                    return if_else(a0 < a1, a1, a0);
        }
      }
      else
        return arithmetic_call(max[o],  r_t(r0), r_t(r1));
    }
    else // N > 2 parameters
    {
      auto m = max[o];
      r_t that(m(r_t(r0), r_t(r1)));
      ((that = m(that, r_t(rs))), ...);
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
    if      constexpr( std::same_as<Callable, std::remove_const<decltype(eve::is_less)>>    ) return eve::max;
    else if constexpr( std::same_as<Callable, std::remove_const<decltype(eve::is_greater)>> ) return eve::min;
    else
    {
      return [f](auto x, auto y){ return eve::if_else(f(y, x), x, y); };
    };
  }
}
