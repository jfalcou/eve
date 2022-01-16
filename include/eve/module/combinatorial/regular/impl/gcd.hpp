//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>

namespace eve::detail
{
  template<value T, value U>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(gcd, a, b);
  }

  template<integral_scalar_value T>
  auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    a = eve::abs(a);
    b = eve::abs(b);
    while( b )
    {
      auto r = a % b;
      a   = b;
      b   = r;
    }
    return a;
  }

  template<integral_simd_value T>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      a = abs(a);
      b = abs(b);
      using elt_t = element_type_t<T>;
      if constexpr(sizeof(elt_t) == 8)
      {
        auto test = is_nez(b);
        T r(0);
        while (eve::any(test))
        {
          b = if_else(test, b, allbits);
          r = a % b;
          a = if_else(test, b, a);
          test = test && is_nez(r);
          b = r;
        }
        return a;
      }
      else if  constexpr(sizeof(elt_t) == 4)
      {

        auto r = raw(gcd)(float64(a), float64(b));
        if constexpr(std::is_signed_v < elt_t>)
          return int32(r);
        else
          return uint32(r);
      }
      else if constexpr(sizeof(elt_t) <= 2)
      {
        auto r = raw(gcd)(float32(a), float32(b));
        if constexpr(sizeof(elt_t) == 2)
        {
          if constexpr(std::is_signed_v < elt_t>)
            return int16(r);
          else
            return uint16(r);
        }
        else
        {
          if constexpr(std::is_signed_v < elt_t>)
            return int8(r);
          else
            return uint8(r);
        }
      }

    }
    else
    {
      return apply_over(gcd, a, b);
    }
  }

  template<floating_value T>
  auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      EVE_ASSERT(eve::all(is_flint(a) && is_flint(b)), "gcd: some entries are not flint");
      a = abs(a);
      b = abs(b);
      if constexpr( scalar_value<T> )
      {
        while( b )
        {
          auto r = rem(a, b);
          a   = b;
          b   = r;
        }
        return a;
      }
      else
      {
        auto test = is_nez(b);
        T r(0);
        while (eve::any(test))
        {
          r = rem(a, b);
          a = if_else(test, b, a);
          test = is_nez(r)&&test;
          b = r;
        }
        return a;
      }
    }
    else
    {
      return apply_over(gcd, a, b);
    }

  }

  template<floating_value T>
  auto gcd_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      a =  eve::abs(a);
      b =  eve::abs(b);
      if constexpr( scalar_value<T> )
      {
        while( b )
        {
          auto r = rem(a, b);
          a   = b;
          b   = r;
        }
        return a;
      }
      else
      {
        auto test = is_nez(b);
        T r(0);
        while (eve::any(test))
        {
          r = rem(a, b);
          a = if_else(test, b, a);
          test = is_nez(r)&&test;
          b = r;
        }
        return a;
      }
    }
    else
    {
      return apply_over(gcd, a, b);
    }
  }

  template<integral_value T>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    return gcd(a, b);
  }
}
