//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_HYPOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_HYPOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto hypot_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point, T>,
            behave_as<floating_point, U>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return hypot(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return hypot(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<abi_type_t<T>>) { return aggregate(eve::hypot, a, b); }
        else if constexpr(is_emulated_v<abi_type_t<T>>)
        {
          return map(eve::hypot, a, b);
        }
        else
        {
          return eve::sqrt(fma(a, a, sqr(b)));
        }
      }
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto hypot_(EVE_SUPPORTS(cpu_)
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
      return pedantic_(hypot)(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return pedantic_(hypot)(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        if constexpr(is_aggregated_v<abi_type_t<T>>)
        {
          return aggregate(pedantic_(eve::hypot), a, b);
        }
        else if constexpr(is_emulated_v<abi_type_t<T>>)
        {
          return map(pedantic_(eve::hypot), a, b);
        }
        else
        {
          if constexpr(std::is_same_v<value_type_t<T>, float>)
          {
            return convert(pedantic_(hypot)(convert(a, double_), convert(b, double_)), single_); 
          }
          else
          {
            using iT = as_integer_t<T>;
            T r =  eve::abs(a);
            T i =  eve::abs(b);
            iT e =  exponent(eve::max(i, r));
            e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
            auto tmp = pedantic_(ldexp)(r, -e); 
            T res =  pedantic_(ldexp)(sqrt(fma(tmp, tmp, sqr(pedantic_(ldexp)(i, -e)))), e);
            if constexpr(eve::platform::supports_invalids)
            {
              return if_else(logical_or(is_infinite(a), is_infinite(b)), Inf<T>(), res);
            }
            else  return res;
          }
        }
      }  
    }
  }

  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  hypot_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept requires(
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
      return hypot(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return hypot(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return hypot(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return hypot(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return hypot(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return hypot(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::hypot, a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::hypot, a, b, c);
        else
          return sqrt(fma(a, a, fma(b, b, sqr(c))));
      }
      return  T();
    }
  }
  
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  hypot_(EVE_SUPPORTS(cpu_)
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
      return pedantic_(hypot)(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return pedantic_(hypot)(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return pedantic_(hypot)(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return pedantic_(hypot)(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return pedantic_(hypot)(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return pedantic_(hypot)(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::pedantic_(hypot), a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::pedantic_(hypot), a, b, c);
        else
        {
          if constexpr(std::is_same_v<value_type_t<T>, float>)
          {
            return convert(pedantic_(hypot)(convert(a, double_), convert(b, double_), convert(c, double_)), single_); 
          }
          else
          {
            using iT = as_integer_t<T>;
            T r =  eve::abs(a);
            T i =  eve::abs(b);
            T j =  eve::abs(c);
            iT e =  exponent(eve::max(eve::max(i, r), j));
            e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
            auto tmpr = pedantic_(ldexp)(r, -e);
            auto tmpi = pedantic_(ldexp)(i, -e);
            auto tmpj = pedantic_(ldexp)(j, -e);    
            T res =  pedantic_(ldexp)(eve::sqrt(fma(tmpr, tmpr, fma(tmpi, tmpi, sqr(tmpj)))), e);   
            if constexpr(eve::platform::supports_invalids)
            {
              return if_else(logical_or(is_infinite(a), logical_or(is_infinite(b), is_infinite(c))), Inf<T>(), res);
            }
            else  return res;
          }
        }
      }
      return  T();
    }
  }
}

#endif
