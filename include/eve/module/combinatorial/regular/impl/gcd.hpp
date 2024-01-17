//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{

  template<typename T, typename U, callable_options O>
  common_value_t<T, U>
  gcd_(EVE_REQUIRES(cpu_), O const& o, T a, U b)
  {
    if constexpr(!std::same_as<T, U>)
    {
      using c_t =  common_value_t<T, U>;
      return gcd_(EVE_TARGETS(cpu_), o, c_t(a), c_t(b)); ;
    }
    else if constexpr(O::contains(raw2))
    {
      if constexpr( has_native_abi_v<T> )
      {
        a = eve::abs(a);
        b = eve::abs(b);
        if constexpr( scalar_value<T> )
        {
          while( b )
          {
            auto r = rem(a, b);
            a      = b;
            b      = r;
          }
          return a;
        }
        else
        {
          auto test = is_nez(b);
          T    r(0);
          while( eve::any(test) )
          {
            r    = rem(a, b);
            a    = if_else(test, b, a);
            test = is_nez(r) && test;
            b    = r;
          }
          return a;
        }
      }
      else { return apply_over(gcd[raw], a, b); }
    }
    else
    {
      if constexpr(integral_scalar_value<T>)
      {
        a = eve::abs(a);
        b = eve::abs(b);
        while( b )
        {
          auto r = a % b;
          a      = b;
          b      = r;
        }
        return a;
      }
      else if constexpr(integral_simd_value<T>)
      {
        if constexpr( has_native_abi_v<T> )
        {
          a           = abs(a);
          b           = abs(b);
          using elt_t = element_type_t<T>;
          if constexpr( sizeof(elt_t) == 8 )
          {
            auto test = is_nez(b);
            T    r(0);
            while( eve::any(test) )
            {
              b    = if_else(test, b, allbits);
              r    = a % b;
              a    = if_else(test, b, a);
              test = test && is_nez(r);
              b    = r;
            }
            return a;
          }
          else if constexpr( sizeof(elt_t) == 4 )
          {
            auto r = gcd[raw](float64(a), float64(b));
            if constexpr( std::is_signed_v<elt_t> ) return int32(r);
            else return uint32(r);
          }
          else if constexpr( sizeof(elt_t) <= 2 )
          {
            auto r = gcd[raw](float32(a), float32(b));
            if constexpr( sizeof(elt_t) == 2 )
            {
              if constexpr( std::is_signed_v<elt_t> ) return int16(r);
              else return uint16(r);
            }
            else
            {
              if constexpr( std::is_signed_v<elt_t> ) return int8(r);
              else return uint8(r);
            }
          }
        }
        else { return apply_over(gcd, a, b); }
      }
      else if constexpr(floating_value<T>)
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
              a      = b;
              b      = r;
            }
            return a;
          }
          else
          {
            auto test = is_nez(b);
            T    r(0);
            while( eve::any(test) )
            {
              r    = rem(a, b);
              a    = if_else(test, b, a);
              test = is_nez(r) && test;
              b    = r;
            }
            return a;
          }
        }
        else { return apply_over(gcd, a, b); }
      }
    }
  }
}
