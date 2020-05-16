//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_OPERATORS_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_OPERATORS_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve
{
  //================================================================================================
  // operator+
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator+( T a, U b) noexcept requires compatible_values<T, U>
  {
    if constexpr( scalar_value<T> ) return b += a;
    else                            return a += b;
  }

  //================================================================================================
  // operator-
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator-( T a, U b) noexcept requires compatible_values<T, U>
  {
    if constexpr( scalar_value<T> ) return U{a} -= b;
    else                            return a    -= b;
  }

  //================================================================================================
  // operator*
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator*( T a, U b) noexcept requires compatible_values<T, U>
  {
    if constexpr( scalar_value<T> ) return b *= a;
    else                            return a *= b;
  }

  //================================================================================================
  // operator/
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator/( T a, U b) noexcept requires compatible_values<T, U>
  {
    if constexpr( scalar_value<T> ) return U{a} /= b;
    else                            return a    /= b;
  }

  //================================================================================================
  // operator%
  //================================================================================================
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE auto operator%( T a, U b) noexcept requires compatible_values<T, U>
  {
    if constexpr( scalar_value<T> ) return U{a} %= b;
    else                            return a    %= b;
  }

  //================================================================================================
  // operator&
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator&( T a, U b) noexcept requires bit_compatible_values<T,U>
  {
    if constexpr( scalar_value<T> ) return bit_cast(b, as<as_wide_t<T, cardinal_t<U>>>()) &= a;
    else                            return a &= b;
  }

  //================================================================================================
  // operator|
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator|( T a, U b) noexcept requires bit_compatible_values<T,U>
  {
    if constexpr( scalar_value<T> ) return bit_cast(b, as<as_wide_t<T, cardinal_t<U>>>()) |= a;
    else                            return a |= b;
  }

  //================================================================================================
  // operator^
  //================================================================================================
  template<value T, value U>
  EVE_FORCEINLINE auto operator^( T a, U b) noexcept requires bit_compatible_values<T,U>
  {
    if constexpr( scalar_value<T> ) return bit_cast(b, as<as_wide_t<T, cardinal_t<U>>>()) ^= a;
    else                            return a ^= b;
  }
}

namespace eve::detail
{
  //================================================================================================
  // infix add
  //================================================================================================
  template<real_scalar_value T>
  EVE_FORCEINLINE  auto  add_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a + b);
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a + b;
  }

  //================================================================================================
  // infix sub
  //================================================================================================
  template<real_scalar_value T>
  EVE_FORCEINLINE  auto  sub_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a - b);
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  sub_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a - b;
  }

  //================================================================================================
  // infix mul
  //================================================================================================
  template<real_scalar_value T>
  EVE_FORCEINLINE  auto  mul_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a * b);
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a * b;
  }

  //================================================================================================
  // infix div
  //================================================================================================
  template<real_scalar_value T>
  EVE_FORCEINLINE  auto  div_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a / b);
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a / b;
  }

  //================================================================================================
  // infix bit_and
  //================================================================================================
  template<real_scalar_value T, real_scalar_value U>
  EVE_FORCEINLINE  auto  bit_and_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires bit_compatible_values<T, U>
  {
    if constexpr(floating_value<T> || floating_value<U>)
    {
      using b_t = as_integer_t<T, unsigned>;
      auto ba = bit_cast( a           , as<b_t>() );
      auto bb = bit_cast( b           , as<b_t>() );
      return    bit_cast( b_t(ba & bb), as(a)     );
    }
    else
    {
      return static_cast<T>(a & b);
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  bit_and_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires bit_compatible_values<T, U>
  {
    return a & b;
  }

  //================================================================================================
  // infix bit_or
  //================================================================================================
  template<real_scalar_value T, real_scalar_value U>
  EVE_FORCEINLINE  auto  bit_or_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires bit_compatible_values<T, U>
  {
    if constexpr(floating_value<T> || floating_value<U>)
    {
      using b_t = as_integer_t<T, unsigned>;
      auto ba = bit_cast( a           , as<b_t>() );
      auto bb = bit_cast( b           , as<b_t>() );
      return    bit_cast( b_t(ba | bb), as(a)     );
    }
    else
    {
      return static_cast<T>(a | b);
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  bit_or_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires bit_compatible_values<T, U>
  {
    return a | b;
  }

  //================================================================================================
  // infix bit_xor
  //================================================================================================
  template<real_scalar_value T, real_scalar_value U>
  EVE_FORCEINLINE  auto  bit_xor_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires bit_compatible_values<T, U>
  {
    if constexpr(floating_value<T> || floating_value<U>)
    {
      using b_t = as_integer_t<T, unsigned>;
      auto ba = bit_cast( a           , as<b_t>() );
      auto bb = bit_cast( b           , as<b_t>() );
      return    bit_cast( b_t(ba ^ bb), as(a)     );
    }
    else
    {
      return static_cast<T>(a ^ b);
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  bit_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires bit_compatible_values<T, U>
  {
    return a ^ b;
  }
}

#endif
