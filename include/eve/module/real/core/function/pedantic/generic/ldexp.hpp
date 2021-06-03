//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/any.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

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
      auto denormal =  b < minexponent(eve::as<T>());
      if (denormal)
      {
        b = sub[denormal]( b, decltype(b)(minexponent(eve::as<T>())));
        auto f = if_else(denormal, smallestposval(eve::as<T>()), eve::one);
        auto test = (b == decltype(b)(limitexponent(eve::as<T>())));
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
    return pedantic(ldexp)(a, convert(b, as<i_t>()));
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
        auto test = (b == decltype(b)(limitexponent(eve::as<elt_t>())));
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
}
