//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/round.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>


#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<value T, value U>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(gcd, a, b);
  }

  template<integral_scalar_value T>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    while( b )
    {
      auto r = a % b;
      a   = b;
      b   = r;
    }
    return eve::abs(a);
  }

  template<integral_simd_value T>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
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
        return eve::abs(a);
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
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto valid = is_flint(a) && is_flint(b);
      if constexpr( scalar_value<T> )
      {
        if (valid)
        {
          while( b )
          {
            auto r = rem(a, b);
            a   = b;
            b   = r;
          }
          return eve::abs(a);
        }
        else return nan(as(a));
      }
      else
      {
        a = if_else(valid, a, zero);
        b = if_else(valid, b, zero);
        auto test = is_nez(b);
        T r(0);
        while (eve::any(test))
        {
          r = rem(a, b);
          a = if_else(test, b, a);
          test = is_nez(r)&&test;
          b = r;
        }
        return if_else(valid, eve::abs(a), allbits);
      }
    }
    else
    {
      return apply_over(gcd, a, b);
    }

  }

  template<floating_value T>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        while( b )
        {
          auto r = rem(a, b);
          a   = b;
          b   = r;
        }
        return eve::abs(a);
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
        return eve::abs(a);
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
    return eve::abs(gcd(a, b));
  }

  template<value T, value U, decorator D>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), D const &, T a, U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(D(gcd), eve::abs(a), eve::abs(b));
  }

  template<value T, decorator D>
  EVE_FORCEINLINE auto gcd_(EVE_SUPPORTS(cpu_), D const &, T a, T b) noexcept
  {
    if constexpr(floating_value<T>)
      return raw(gcd)(D()(round)(a), D()(round)(b));
    else
      return raw(gcd)(a, b);
  }

}
