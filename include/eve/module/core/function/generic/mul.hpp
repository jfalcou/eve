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
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  //================================================================================================
  // saturated case
  //================================================================================================
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated_(mul), a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  {
    if constexpr( floating_value<T> )
    {
      return static_cast<T>(a * b);
    }
    else if constexpr( std::is_signed_v<T> )
    {
      if constexpr( sizeof(T) <= 2 )
      {
        using up_t = upgrade_t<T>;
        return static_cast<T>(saturate(static_cast<up_t>(a) * static_cast<up_t>(b), as<T>()));
      }
      else if constexpr( sizeof(T) == 4 )
      {
        using un_t = std::make_unsigned_t<T>;
        using up_t = int64_t;
        enum Sizee
        {
          value = sizeof(T) * 8 - 1
        };

        up_t res  = up_t(a) * up_t(b);
        un_t res2 = (un_t(a ^ b) >> Sizee::value) + Valmax<T>();
        T    hi   = (res >> (Sizee::value + 1));
        T    lo   = res;
        if( hi != (lo >> Sizee::value) )
          res = res2;
        return static_cast<T>(res);
      }
      else if constexpr( sizeof(T) == 8 )
      {
        using un_t = std::make_unsigned_t<T>;
        if( b == 0 || a == 0 )
          return Zero<T>();
        T sgn = bit_xor(bitofsign(a), bitofsign(b));
        if( b == Valmin<T>() || a == Valmin<T>() )
          return sgn ? Valmin<T>() : Valmax<T>();
        un_t aa  = eve::abs(a);
        un_t bb  = eve::abs(b);
        auto aux = [sgn](const T &mini, const T &maxi, const un_t &amini, const un_t &amaxi) {
          un_t z = Valmax<T>() / amaxi;
          return (z < amini) ? (sgn ? Valmin<T>() : Valmax<T>()) : mini * maxi;
        };
        if( bb >= aa )
          return aux(a, b, aa, bb);
        else
          return aux(b, a, bb, aa);
      }
    }
    else if constexpr( std::is_unsigned_v<T> )
    {
      if constexpr( sizeof(T) <= 4 )
      {
        using up_t = upgrade_t<T>;
        up_t res   = up_t(a) * up_t(b);
        return (res > Valmax<T>()) ? Valmax<T>() : static_cast<T>(res);
      }
      else
      {
        auto aux = [](const T &mini, const T &maxi) {
          T z = Valmax<T>() / maxi;
          return (z < mini) ? Valmax<T>() : mini * maxi;
        };
        if( b == 0 || a == 0 )
          return Zero<T>();
        if( b >= a )
          return aux(a, b);
        else
          return aux(b, a);
      }
    }
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    using elt_t = element_type_t<T>;
    if constexpr( floating_value<T> )
    {
      return a * b;
    }
    else if constexpr( integral_value<T> )
    {
      if constexpr( sizeof(elt_t) <= 4 )
      {
        using sup_t = upgrade_t<elt_t>;
        auto z      = mul(to_<sup_t>(a), to_<sup_t>(b));
        auto s      = saturate(z, as<elt_t>()); // TODO saturated_(convert) ?
        return to_<elt_t>(s);
      }
      else
      {
        auto that = map(saturated_(eve::mul), a, b);
        return that;
      }
    }
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    using r_t = decltype(mul(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond ? mul(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return mul(r_t(t), if_else(cond, r_t(f), eve::one_));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), T const &cond, saturated_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    using r_t = decltype(saturated_(mul)(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond ? saturated_(mul)(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return saturated_(mul)(r_t(t), if_else(cond, r_t(f), eve::one_));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), not_t<T> const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    using r_t = decltype(mul(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond.value ? r_t(t) : mul(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return mul(r_t(t), if_else(cond.value, eve::one_, r_t(f)));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(cpu_),
                            not_t<T> const &cond,
                            saturated_type const &,
                            U const &t,
                            V const &f) noexcept requires compatible_values<U, V>
  {
    using r_t = decltype(mul(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond.value ? r_t(t) : saturated_(mul)(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return saturated_(mul)(r_t(t), if_else(cond.value, eve::one_, r_t(f)));
    }
  }
}
