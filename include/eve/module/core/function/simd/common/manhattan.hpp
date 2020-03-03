//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MANHATTAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MANHATTAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/inf.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto manhattan_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point, T>,
            behave_as<floating_point, U>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return manhattan(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return manhattan(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<abi_type_t<T>>) { return aggregate(eve::manhattan, a, b); }
        else if constexpr(is_emulated_v<abi_type_t<T>>)
        {
          return map(eve::manhattan, a, b);
        }
        else
        {
          return  eve::abs(a)+eve::abs(b);
        }
      }
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto manhattan_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point,T>,
            behave_as<floating_point,U>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return pedantic_(manhattan)(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return pedantic_(manhattan)(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<abi_type_t<T>>)
        {
          return aggregate(pedantic_(eve::manhattan), a, b);
        }
        else if constexpr(is_emulated_v<abi_type_t<T>>)
        {
          return map(pedantic_(eve::manhattan), a, b);
        }
        else
        {
          auto test = logical_or(is_infinite(a), is_infinite(b));
          auto res = manhattan(a, b); 
          if constexpr(eve::platform::supports_invalids)
          {
            return if_else(test, Inf<T>(), res);
          }
          else return res;
        }
      }  
    }
  }

  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  manhattan_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept requires(
      std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>, 
      behave_as<floating_point, T>,
      behave_as<floating_point, U>, 
      behave_as<floating_point, V>)
  {
    static constexpr auto vT = is_vectorized_v<T>;
    static constexpr auto vU = is_vectorized_v<U>;
    static constexpr auto vV = is_vectorized_v<V>;

    if constexpr(vT && !vU && !vV)
      return manhattan(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return manhattan(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return manhattan(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return manhattan(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return manhattan(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return manhattan(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::manhattan, a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::manhattan, a, b, c);
        else
          return eve::abs(a)+eve::abs(b)+eve::abs(c);
      }
      return  T();
    }
  }
  
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  manhattan_(EVE_SUPPORTS(cpu_)
        , pedantic_type const &
        , T const &a
        , U const &b
        , V const &c) noexcept requires(
    std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
    detail::either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>, 
    behave_as<floating_point, T>,
    behave_as<floating_point, U>, 
    behave_as<floating_point, V>)
  {
    static constexpr auto vT = is_vectorized_v<T>;
    static constexpr auto vU = is_vectorized_v<U>;
    static constexpr auto vV = is_vectorized_v<V>;
    
    if constexpr(vT && !vU && !vV)
      return pedantic_(manhattan)(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return pedantic_(manhattan)(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return pedantic_(manhattan)(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return pedantic_(manhattan)(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return pedantic_(manhattan)(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return pedantic_(manhattan)(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::pedantic_(manhattan), a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::pedantic_(manhattan), a, b, c);
        else
        {
          auto test = logical_or(is_infinite(a), logical_or(is_infinite(b), is_infinite(c)));
          auto res = manhattan(a, b, c); 
          if constexpr(eve::platform::supports_invalids)
          {
            return if_else(test, Inf<T>(), res);
          }
          else return res;
        }
      }
      return  T();
    }
  }
}

#endif
