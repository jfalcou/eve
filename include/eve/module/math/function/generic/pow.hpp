//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

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
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sqr.hpp>

////////////////////////////////////////////////////////////////////////////////////
// some benches results                                        clang10
// AVX2 FMA
// std_pow  - float                                        29.8664
// std_pow  - double                                       98.7585
// eve::pow - eve::wide<float, eve::fixed<8l>, eve::avx_>  19.2366
// eve::pow - eve::wide<double, eve::fixed<4l>, eve::avx_> 68.0063 
// eve::pow - float                                        30.6931  - using std
// eve::pow - double                                       88.7653  - using std


namespace eve::detail
{
  /////////////////////////////////////////////////////////////////////////////
  // floating parameters
  /////////////////////////////////////////////////////////////////////////////
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), raw_type const&, T a, U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(raw_(pow), a, b);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pow, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr(scalar_value<T>)                  // for now scalar uses std::
    {
      if constexpr(std::is_same_v<T, float>)
      {
        return std::pow(a, b);
      }
      else
      {
        auto ltza   = is_ltz(a);
        auto isinfb = is_infinite(b);
        if( a == Mone<T>() && isinfb )                return One<T>();
        if( ltza && !is_flint(b) && !is_infinite(b) ) return Nan<T>();
        auto z = pow_abs(a, b);
        if( isinfb )                                  return z;
        return (is_negative(a) && is_odd(b)) ? -z : z;
      }
    }
    else  if constexpr(has_native_abi_v<T> )
    {
      using elt_t =  element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto std_pow = [](auto const & a,  auto const & b){ return std::pow(a, b);};
        return map(std_pow, a, b);
      }
      else
      {
        auto isinfb = is_infinite(b);
        auto nega    = is_negative(a);
        a =  if_else( a == Mone<T>() && isinfb , One(as(a)), a);
        T    z       = pow_abs(a, b);
        z            = minus[logical_and(is_odd(b), nega)](z);
        auto invalid = logical_andnot(nega, logical_or(is_flint(b), is_infinite(b)));
        return if_else(invalid, eve::allbits_, z);
      }
    }
    else
    {
      return apply_over(pow, a, b);
    }

  }

  //////////////////////////////////////////////////////////////////////////////////////////
  // raw
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(raw_(pow_abs), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    if constexpr(has_native_abi_v<T> )
    {
      return if_else(is_ltz(a), eve::allbits_, pow_abs(raw_type(), a, b));
    }
    else return apply_over(raw_(pow), a, b);
  }


  template<floating_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
  {
    if constexpr( std::is_unsigned_v<U> )
    {
      T base = a0;
      U expo = a1;

      T result(1);
      while( expo )
      {
        if( is_odd(expo) )  result *= base;
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

  template<floating_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), raw_type const &, T a0, U a1) noexcept
  {
    return pow(a0, a1);
  }

  template<real_simd_value T, integral_real_simd_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
  {
    if constexpr(integral_value<T>)
    {
      a1 = if_else ( a0 == One(as(a0)), eve::one_, a1);
      auto test = ( (a1 >= U((sizeof(T) * 8 - 1 - std::is_signed_v<T>))) || a1 < 0 );
      a0 = if_else(test, eve::zero_, a0);
      a1 = if_else(test, eve::one_, a1);
    }
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
      return if_else(is_ltz(a1), rec(tmp), tmp);
    }
  }

  template<real_simd_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), raw_type const &, T a0, U a1) noexcept
  {
    return pow(a0, a1);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// integral parameters
  template<integral_real_value T, integral_real_scalar_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
  {
    if( a1 >= U(sizeof(T) * 8 - 1 - (std::is_signed_v<T>)) || a1 < 0) return T(0);
    constexpr uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
    // anything past 63 is a guaranteed overflow with base > 1
    T result(1);
    switch( highest_bit_set[a1] )
    {
    case 6:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 5:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1; a0 *= a0;
    case 4:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 3:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 2:
      if( a1 & 1 )
        result *= a0;
      a1 >>= 1; a0 *= a0;
    case 1:
      if( a1 & 1 ) result *= a0;
    default:
      return result;
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
        if( is_odd(expo) ) result *= base;
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
    if( a0 == 1 ) return 1;
    if( (a1 >= U((sizeof(T) * 8 - 1 - std::is_signed_v<T>))) || a1 < 0 ) return 0;
    constexpr uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
    // anything past 63 is a guaranteed overflow with base > 1

    T result = 1;
    switch( highest_bit_set[a1] )
    {
    case 6:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 5:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 4:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 3:
      if( a1 & 1 )  result *= a0;
      a1 >>= 1;  a0 *= a0;
    case 2:
      if( a1 & 1 ) result *= a0;
      a1 >>= 1; a0 *= a0;
    case 1:
      if( a1 & 1 )  result *= a0;
    default:
      return result;
    }
  }

  template<integral_real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto pow_(EVE_SUPPORTS(cpu_), raw_type const &, T a, U b) noexcept
  {
    return arithmetic_call(pow, a, b);
  }
}
