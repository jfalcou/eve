//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/is_less.hpp>
#include <eve/module/arithmetic/regular/sub.hpp>
#include <eve/module/arithmetic/regular/trunc.hpp>

namespace eve::detail
{
  //////////////////////////////////////////////////////////
  // floating b
  template<floating_value T, value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T a
                             , U b) noexcept
  {
    return pedantic(ldexp)(a, int_(trunc(b)));
  }

  //////////////////////////////////////////////////////////
  // scalar a and scalar b
  template<floating_real_scalar_value T, integral_scalar_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T a
                             , U b) noexcept
  {
    using i_t =  as_integer_t<T>;
    if constexpr(eve::platform::supports_denormals)
    {
      auto denormal =  b < static_cast<U>(minexponent(eve::as<T>()));
      if (denormal)
      {
        b = sub[denormal]( b, decltype(b)(minexponent(eve::as<T>())));
        auto f = if_else(denormal, smallestposval(eve::as<T>()), eve::one);
        auto test = (b == decltype(b)(maxexponentp1(eve::as<T>())));
        f = inc[test](f);
        b = dec[test](b);
        b += maxexponent(eve::as<T>());
        b <<=  nbmantissabits(eve::as<T>());
        return a*bit_cast(i_t(b), as(T()))*f;
      }
      else return ldexp(a, b);
    }
    else return ldexp(a, b);
  }

  //////////////////////////////////////////////////////////
  // scalar a and simd b
  template<floating_real_scalar_value T, integral_simd_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T a
                             , U b) noexcept
  {
    using i_t =  as_integer_t<T>;
    using w_t =  wide<T,  cardinal_t<U>>;
    return pedantic(ldexp)(w_t(a), convert(b, as<i_t>()));
  }

  //////////////////////////////////////////////////////////
  // simd a and scalar b
  template<floating_real_simd_value T, integral_scalar_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T a
                             , U b) noexcept
  {
    using elt_t = element_type_t<T>;
    using i_t =  as_integer_t<elt_t>;
    using wi_t =  wide<i_t, cardinal_t<T>>;
    return pedantic(ldexp)(a, wi_t(b));
  }

  //////////////////////////////////////////////////////////
  // simd a and simd b
  template<floating_real_simd_value T, integral_simd_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T a
                             , U b) noexcept
  requires (cardinal_v<T> == cardinal_v<U>)
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      using elt_t = element_type_t<T>;
      auto denormal =  is_less(b, minexponent(eve::as<elt_t>()));
      if (eve::any(denormal))
      {
        auto f = one(eve::as<T>());
        if constexpr( eve::platform::supports_denormals)
        {
          b = sub[denormal]( b, decltype(b)(minexponent(eve::as<elt_t>())));
          f = if_else(denormal, smallestposval(eve::as<elt_t>()), eve::one);
        }
        auto test = (b == decltype(b)(maxexponentp1(eve::as<elt_t>())));
        f = inc[test](f);
        b = dec[test](b);
        b += maxexponent(eve::as<elt_t>());
        b <<=  nbmantissabits(eve::as<elt_t>());
        return a*bit_cast(b, as(T()))*f;
      }
      else return ldexp(a, b);
    }
    else  return apply_over(pedantic(ldexp), a, b);
  }

  template<conditional_expr C, floating_real_value T0, real_value T1>
  auto ldexp_(EVE_SUPPORTS(cpu_), C const &cond, pedantic_type const &, T0 a0, T1 a1)
  requires floating_value<common_compatible_t<T0, T1>>
  {
    return mask_op(  cond, pedantic(eve::ldexp), a0, a1);
  }

}
