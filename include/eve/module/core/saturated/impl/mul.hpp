//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/saturated.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/module/core/regular/saturate.hpp>

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
    return arithmetic_call(saturated(mul), a, b);
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
        un_t res2 = (un_t(a ^ b) >> Sizee::value) + valmax(eve::as<T>());
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
          return zero(eve::as<T>());
        T sgn = bit_xor(bitofsign(a), bitofsign(b));
        if( b == valmin(eve::as<T>()) || a == valmin(eve::as<T>()) )
          return sgn ? valmin(eve::as<T>()) : valmax(eve::as<T>());
        un_t aa  = eve::abs(a);
        un_t bb  = eve::abs(b);
        auto aux = [sgn](const T &mini, const T &maxi, const un_t &amini, const un_t &amaxi) {
          un_t z = valmax(eve::as<T>()) / amaxi;
          return (z < amini) ? (sgn ? valmin(eve::as<T>()) : valmax(eve::as<T>())) : mini * maxi;
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
        return (res > valmax(eve::as<T>())) ? valmax(eve::as<T>()) : static_cast<T>(res);
      }
      else
      {
        auto aux = [](const T &mini, const T &maxi) {
          T z = valmax(eve::as<T>()) / maxi;
          return (z < mini) ? valmax(eve::as<T>()) : mini * maxi;
        };
        if( b == 0 || a == 0 )
          return zero(eve::as<T>());
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
        auto s      = saturate(z, as<elt_t>());
        return to_<elt_t>(s);
      }
      else
      {
        auto that = map(saturated(eve::mul), a, b);
        return that;
      }
    }
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> mul_(EVE_SUPPORTS(cpu_), saturated_type const &, T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    r_t that(saturated(mul)(r_t(a0),r_t(a1)));
    ((that = saturated(mul)(that,r_t(args))),...);
   return that;
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, saturated(mul), t, f);
  }
}
