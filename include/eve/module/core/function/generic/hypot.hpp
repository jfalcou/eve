//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_HYPOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_HYPOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/min.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(hypot, a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , T const &a
                             , T const &b
                             ) noexcept

  {
    if constexpr(native<T>) return eve::sqrt(fma(a, a, sqr(b)));
    else                    return  apply_over(hypot, a, b);
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(hypot, a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept

  {
    if constexpr(native<T>) return eve::sqrt(fma(a, a, fma(b, b, sqr(c))));
    else                    return  apply_over(hypot, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // pedantic case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic_(hypot), a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             ) noexcept
  {
    if constexpr(native<T>)
    {
      using elt_t =  element_type_t<T>;
      if constexpr(eve::platform::supports_invalids && scalar_value<T>)
        if (is_infinite(a) || is_infinite(b)) return Inf(as(a));
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto res = convert(hypot(convert(a, double_), convert(b, double_)), single_);
        if constexpr(eve::platform::supports_invalids && simd_value<T>)
          return if_else(is_infinite(a) || is_infinite(b), Inf<T>(), res);
        else return res;
      }
      else
      {
        if constexpr(eve::platform::supports_invalids && scalar_value<T>) if (is_infinite(a) || is_infinite(b)) return Inf(as(a));
        auto e =  exponent(eve::maxmag(a, b));
        e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
        auto tmp = pedantic_(ldexp)(a, -e);
        auto res =  pedantic_(ldexp)(sqrt(fma(tmp, tmp, sqr(pedantic_(ldexp)(b, -e)))), e);
        if constexpr(eve::platform::supports_invalids && simd_value<T>)
          return if_else(is_infinite(a) || is_infinite(b), Inf<T>(), res);
        else return res;
      }
    }
    else return apply_over(pedantic_(hypot), a, b);
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto hypot_(EVE_SUPPORTS(cpu_)
                              , pedantic_type const &
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(pedantic_(hypot), a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto hypot_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept

  {
    if constexpr(native<T>)
    {
      if constexpr(scalar_value<T>)
        if (is_infinite(a)|| is_infinite(b)|| is_infinite(c))  return Inf(as(a));
      if constexpr(std::is_same_v<value_type_t<T>, float>)
      {
        return convert(hypot(convert(a, double_), convert(b, double_), convert(c, double_)), single_);
      }
      else
      {
        auto e =  exponent(eve::maxmag(eve::maxmag(a, b), c));
        e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
        auto tmpr = pedantic_(ldexp)(a, -e);
        auto tmpi = pedantic_(ldexp)(b, -e);
        auto tmpj = pedantic_(ldexp)(c, -e);
        T res =  pedantic_(ldexp)(eve::sqrt(fma(tmpr, tmpr, fma(tmpi, tmpi, sqr(tmpj)))), e);
        if constexpr(eve::platform::supports_invalids)
          return if_else(is_infinite(a) || is_infinite(b) || is_infinite(c), Inf<T>(), res);
        else  return res;
      }
    }
    else return  apply_over(pedantic_(hypot), a, b, c);
  }
}

#endif
