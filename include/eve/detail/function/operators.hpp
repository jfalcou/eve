//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // Infix arithmetic operators
  //================================================================================================
  template<scalar_value T>
  EVE_FORCEINLINE  auto  add_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a + b);
  }

  template<value T, value U>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a + b;
  }

  template<scalar_value T>
  EVE_FORCEINLINE  auto  sub_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a - b);
  }

  template<value T, value U>
  EVE_FORCEINLINE auto
  sub_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a - b;
  }

  template<scalar_value T>
  EVE_FORCEINLINE  auto  mul_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a * b);
  }

  template<value T, value U>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a * b;
  }

  template<scalar_value T>
  EVE_FORCEINLINE  auto  div_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a / b);
  }

  template<value T, value U>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return a / b;
  }

  template<integral_scalar_value T>
  EVE_FORCEINLINE  auto  rem_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    return static_cast<T>(a % b);
  }

  template<integral_value T, integral_value U>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_)
                            , T const &a, U const &b
                            ) noexcept requires compatible_values<T, U>
  {
    return a % b;
  }

  //================================================================================================
  // infix bitwise operators
  //================================================================================================
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bit_and_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires bit_compatible_values<T, U>
  {
    if constexpr(scalar_value<T> && scalar_value<U>)
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
    else
    {
      return a & b;
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bit_or_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires bit_compatible_values<T, U>
  {
    if constexpr(scalar_value<T> && scalar_value<U>)
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
    else
    {
      return a | b;
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bit_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires bit_compatible_values<T, U>
  {
    if constexpr(scalar_value<T> && scalar_value<U>)
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
    else
    {
      return a ^ b;
    }
  }
}
