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

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  max_(EVE_REQUIRES(cpu_), O const & o, T0 a0, T1 a1, Ts... args) noexcept
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0) // 2 parameters
    {
      if constexpr(std::same_as<T0, T1>)
      {
        if constexpr(O::contains(pedantic2)) //pedantic
        {
          if constexpr( eve::platform::supports_invalids )
          {
            if constexpr( scalar_value<T0> )
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
            if constexpr( scalar_value<T0> )
            {
              return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
            }
            else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
          }
        }
        else if  constexpr(O::contains(numeric2))  // numeric
        {
          if constexpr( eve::platform::supports_invalids )
          {
            if constexpr( scalar_value<T0> )
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
            if constexpr( scalar_value<T0> )
            {
              return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::max(a0, a1));
            }
            else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::max(a0, a1)); }
          }
        }
        else
        {
          if constexpr(scalar_value<T0>)
            return a0 < a1 ? a1 : a0;
          else
            return if_else(a0 < a1, a1, a0);
        }
      }
      else
        return arithmetic_call(max[o], a0, a1);
    }
    else // N > 2 parameters
    {
      auto m = max[o];
      r_t that(m(r_t(a0), r_t(a1)));
      ((that = m(that, r_t(args))), ...);
      return that;
    }
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto  max_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  {
    if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
    else
    {
      auto m = eve::max[o];
      return kumi::apply( [&](auto... a) { return eve::max(a...); }, tup);
    }
  }

  //================================================================================================
  // Predicate case
  //================================================================================================
  template<typename Callable, callable_options O>
  EVE_FORCEINLINE constexpr auto
  max_(EVE_REQUIRES(cpu_), O const & o, Callable f) noexcept
  {
    if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::max[o];
//    else if constexpr( std::same_as<Callable, callable_is_greater_> ) return eve::min[o];
    else
    {
      return [f]<typename T0, typename T1, typename... Ts >(T0 a0, T1 a1, Ts... args){
        auto pred = [f](auto x,  auto y){ return eve::if_else(f(x, y), x, y); };
        using r_t = common_value_t<T0, T1, Ts...>;
        r_t that(pred(r_t(a0), r_t(a1)));
        ((that = pred(that, r_t(args))), ...);
        return that;
      };
    }
  }
}
