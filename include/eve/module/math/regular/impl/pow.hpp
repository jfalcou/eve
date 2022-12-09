//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/pow_abs.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
/////////////////////////////////////////////////////////////////////////////
// floating parameters
/////////////////////////////////////////////////////////////////////////////

template<floating_value T, floating_value U>
EVE_FORCEINLINE auto
pow_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(pow, a, b);
}

template<floating_ordered_value T>
EVE_FORCEINLINE auto
pow_(EVE_SUPPORTS(cpu_), T a, T b) noexcept requires has_native_abi_v<T>
{
  if constexpr( scalar_value<T> )
    if( a == mone(as(a)) && is_infinite(b) ) return one(as(a));
  auto nega = is_negative(a);
  T    z    = pow_abs(a, b);
  z         = minus[is_odd(b) && nega](z);
  return z;
}

//////////////////////////////////////////////////////////////////////////////////////////
// raw
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
pow_(EVE_SUPPORTS(cpu_), raw_type const&, T a, U b) noexcept
-> common_value_t<T, U>
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_value<U> )
    {
      if constexpr( simd_value<T> ^ simd_value<U> )
      {
        if constexpr( scalar_value<U> ) return raw(pow)(a, T {b});
        else if constexpr( scalar_value<T> ) return raw(pow)(U {a}, b);
      }
      else
      {
        if constexpr( std::is_same_v<T, U> ) { return exp(b * log(a)); }
      }
    }
    else { return pow(a, b); }
  }
  else return apply_over(raw(pow), a, b);
}

//////////////////////////////////////////////////////////////////////////////////////////
// integral second parameter
template<value T, integral_value U>
EVE_FORCEINLINE constexpr auto
pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
{
  if constexpr(scalar_value<U>)
  {
    if constexpr( std::is_unsigned_v<U> )
    {
      T base = a0;
      U expo = a1;

      auto result = one(as(a0));
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
      return if_else(is_ltz(a1), rec(tmp), tmp);
    }
  }
  else // simd case
  {
    if constexpr( unsigned_value<U> )
    {
      T base = a0;
      U expo = a1;

      T result(1);
      while( eve::any(to_logical(expo)) )
      {
        result *= if_else(is_odd(expo), base, T(1));
        expo = (expo >> 1);
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
}

template<floating_scalar_value T, integral_simd_value U>
EVE_FORCEINLINE constexpr auto
pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
{
  using r_t = wide<T, cardinal_t<U>>;
  return pow(r_t(a0), a1);
}

template<integral_value T, integral_value U>
constexpr auto
pow_(EVE_SUPPORTS(cpu_), T a0, U a1) noexcept
requires scalar_value<U>
{
  if( a1 >= U(sizeof(T) * 8 - 1 - (std::is_signed_v<T>)) || a1 < 0 ) return T(0);
  constexpr uint8_t highest_bit_set[] = {
      0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
      6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}; // anything past 63 is a
                                                                      // guaranteed overflow with
                                                                      // base >
                                                                      // 1

  T result(1);
  switch( highest_bit_set[a1] )
  {
  case 6:
    if( a1 & 1 ) result *= a0;
    a1 >>= 1;
    a0 *= a0;
    [[fallthrough]];
  case 5:
    if( a1 & 1 ) result *= a0;
    a1 >>= 1;
    a0 *= a0;
    [[fallthrough]];
  case 4:
    if( a1 & 1 ) result *= a0;
    a1 >>= 1;
    a0 *= a0;
    [[fallthrough]];
  case 3:
    if( a1 & 1 ) result *= a0;
    a1 >>= 1;
    a0 *= a0;
    [[fallthrough]];
  case 2:
    if( a1 & 1 ) result *= a0;
    a1 >>= 1;
    a0 *= a0;
    [[fallthrough]];
  case 1:
    if( a1 & 1 ) result *= a0;
    [[fallthrough]];
  default: return result;
  }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value T , value U>
EVE_FORCEINLINE auto
pow_(EVE_SUPPORTS(cpu_), C const& cond, T const& t, U const& u) noexcept
-> decltype( if_else(cond, pow(t, u), t) )
{
  return mask_op(cond, eve::pow, t, u);
}
}
