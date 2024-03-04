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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/max.hpp>

namespace eve::detail
{

  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  min_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
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
          if constexpr( eve::platform::supports_invalids )
          {
            if constexpr( scalar_value<T0> )
            {
              if( is_eqz(a0) && is_eqz(a1) ) return bit_and(a0, a1);
              return is_unordered(a0, a1) ? a0 : eve::min(a0, a1);
            }
            else
            {
              auto tmp = if_else(is_unordered(a0, a1), a0, eve::min(a0, a1));
              return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), tmp);
            }
          }
          else
          {
            if constexpr(is_scalar)
            {
              return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::min(a0, a1));
            }
            else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::min(a0, a1)); }
          }
        }
        else if  constexpr(O::contains(numeric2))  // numeric
        {
          if constexpr( eve::platform::supports_invalids )
          {
            if constexpr(is_scalar)
            {
              if( is_eqz(a0) && is_eqz(a1) ) return bit_and(a0, a1);
              return is_nan(a0) ? a1 : is_nan(a1) ? a0 : min(a0, a1);
            }
            else
            {
              auto tmp = if_else(is_nan(a0), a1, if_else(is_nan(a1), a0, min(a0, a1)));
              return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), tmp);
            }
          }
          else
          {
            if constexpr(is_scalar)
            {
              return (is_eqz(a0) && is_eqz(a1) ? bit_and(a0, a1) : eve::min(a0, a1));
            }
            else { return if_else(is_eqz(a0) && is_eqz(a1), bit_and(a0, a1), eve::min(a0, a1)); }
          }
        }
        else
        {
          if constexpr(is_scalar)
            return a0 < a1 ? a1 : a0;
          else
            return if_else(a0 < a1, a0, a1);
        }
      }
      else
        return arithmetic_call(min[o],  r_t(r0), r_t(r1));
    }
    else // N > 2 parameters
    {
      auto m = min[o];
      r_t that(m(r_t(r0), r_t(r1)));
      ((that = m(that, r_t(rs))), ...);
      return that;
    }
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto  min_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  {
    if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
    else
    {
      auto m = eve::min[o];
      return kumi::apply( [&](auto... a) { return eve::min(a...); }, tup);
    }
  }

  //================================================================================================
  // Predicate case
  //================================================================================================
  template<typename Callable, callable_options O>
  EVE_FORCEINLINE constexpr auto
  min_(EVE_REQUIRES(cpu_), O const & o, Callable f) noexcept
  {
    if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::min[o];
    else if constexpr( std::same_as<Callable, callable_is_greater_> ) return eve::max[o];
    else
    {
      return [f]<typename T0, typename T1, typename... Ts >(T0 x, T1 y){
        return eve::if_else(f(x, y), x, y); };
    };
  }

//   template<typename Callable, callable_options O>
//   EVE_FORCEINLINE constexpr auto
//   min_(EVE_REQUIRES(cpu_), O const & o, Callable f) noexcept
//   {
//     if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::min[o];
//     else if constexpr( std::same_as<Callable, callable_is_greater_> ) return eve::max[o];
//     else
//     {
//       return [f]<typename T0, typename T1, typename... Ts >(T0 a0, T1 a1, Ts... args){
//         auto pred = [f](auto x,  auto y){ return eve::if_else(f(x, y), x, y); };
//         using r_t = common_value_t<T0, T1, Ts...>;
//         r_t that(pred(r_t(a0), r_t(a1)));
//         ((that = pred(that, r_t(args))), ...);
//         return that;
//       };
//     }
//   }

}
