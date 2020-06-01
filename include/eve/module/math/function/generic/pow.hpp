//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_MATH_FUNCTION_GENERIC_POW_HPP_INCLUDED
#define EVE_MODULE_MATH_FUNCTION_GENERIC_POW_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sqr.hpp>

namespace eve::detail
{
  /////////////////////////////////////////////////////////////////////////////
  // floating parameters
  /////////////////////////////////////////////////////////////////////////////
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pow, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      auto ltza   = is_ltz(a);
      auto isinfb = is_infinite(b);
      if( a == Mone<T>() && isinfb )                return One<T>();
      if( ltza && !is_flint(b) && !is_infinite(b) ) return Nan<T>();
      auto z = pow_abs(a, b);
      if( isinfb )                                  return z;
      return (is_negative(a) && is_odd(b)) ? -z : z;
    }
    else  if constexpr(has_native_abi_v<T> )
    {
      auto nega    = is_negative(a);
      T    z       = pow_abs(a, b);
      z            = minus[logical_and(is_odd(b), nega)](z);
      auto invalid = logical_andnot(nega, logical_or(is_flint(b), is_infinite(b)));
      return if_else(invalid, eve::allbits_, z);
    }
    else return apply_over(pow, a, b);
  }

  //////////////////////////////////////////////////////////////////////////////////////////
  // raw
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, U const &b) noexcept
  {
    if constexpr( floating_value<U> )
    {
      if constexpr( scalar_value<U> )  return pow(a, T {b});
      else if constexpr(  scalar_value<T> ) return pow(U {a}, b);
      else
      {
        if constexpr( std::is_same_v<T, U> )
        {
           return exp(b * log(a));
        }
      }
    }
    else
    {
      return pow(a, b);
    }
  }

  template<floating_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept
  {
    if constexpr( std::is_unsigned_v<U> )
    {
      T base = a0;
      U expo = a1;

      T result(1);
      while( expo )
      {
        if( is_odd(expo) )
          result *= base;
        expo >>= 1;
        base = sqr(base);
      }
      return result;
    }
    else
    {
      using u_t = as_integer_t<U, unsigned>;
      T tmp     = pow(a0, u_t(eve::abs(a1)));
      return if_else(is_ltz(a1), rec(tmp), tmp);
    }
  }

  template<real_simd_value T, integral_real_simd_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept
  {
    if constexpr(unsigned_value<U> )
    {
      T base = a0;
      U expo = a1;

      T result(1);
      while( any(expo) )
      {
        result *= if_else(is_odd(expo), base, T(1));
        expo = shr(expo, 1);
        base = sqr(base);
      }
      return result;
    }
    else
    {
      using u_t = as_integer_t<U, unsigned>;
      T tmp     = pow(a0, bit_cast(eve::abs(a1), as<u_t>()));
      return minus[a0 < 0 && is_odd(a1)](tmp);
    }
  }

  template<integral_real_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
  {
    if( a1 >= U(sizeof(T) * 8 - 1 - (std::is_signed_v<T>)) || a1 < 0 )
      return T(0);
    constexpr uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}; // anything past 63 is a
                                                                  // guaranteed overflow with base >
                                                                  // 1

    T result(1);
    switch( highest_bit_set[a1] )
    {
    case 6:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 5:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 4:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 3:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 2:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 1:
      if( a1 & 1 )
        result *= a0;
    default: return result;
    }
  }



  template<floating_real_scalar_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept
  {
    if constexpr( std::is_unsigned_v<U> )
    {
      T base = a0;
      U expo = a1;

      T result(1);
      while( expo )
      {
        if( is_odd(expo) )
          result *= base;
        expo >>= 1;
        base = sqr(base);
      }
      return result;
    }
    else
    {
      using u_t = as_integer_t<U, unsigned>;
      T tmp     = pow(a0, u_t(eve::abs(a1)));
      return if_else(a1 < 0, rec(tmp), tmp);
    }
  }

  template<integral_real_scalar_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr T pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
  {
    if( a0 == 1 )
      return 1;
    if( (a1 >= U((sizeof(T) * 8 - 1 - std::is_signed_v<T>))) || a1 < 0 )
      return 0;
    constexpr uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}; // anything past 63 is a
                                                                  // guaranteed overflow with base >
                                                                  // 1

    T result = 1;
    switch( highest_bit_set[a1] )
    {
    case 6:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 5:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 4:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 3:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 2:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1;
      a0 *= a0;
    case 1:
      if( a1 & 1 )
        result *= a0;
    default: return result;
    }
  }
}

#endif
