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

#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/next.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  //////////////////////////////////////////////////////////////
  // regular call
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        return bitfloating(dec(bitinteger(a)));
      }
      else if constexpr(integral_value<T>)
      {
        return dec(a);
      }
    }
    else
    {
      return apply_over(prev, a);
    }
  }


//////////////////////////////////////////////////////////////
  // pedantic call
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      ,  pedantic_type const &
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto nz = bitinteger(a);
        auto z  = bitfloating( dec(nz) );
        auto test = is_negative(z) && is_positive(a);
        if constexpr(scalar_value<T>)
        {
          return test ? (a == 0 ? T(-0.) : bitfloating(nz)) : z;
        }
        else
        {
          return if_else(test, if_else(is_eqz(a), mzero(eve::as(a)), bitfloating(nz)), z);
        }
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(dec)(a);
      }
    }
    else  { return apply_over(pedantic(prev), a);    }
  }

  ////////////////////////////////////////////////
  // saturated
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const &
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto z =  prev(a);
        if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits, z);
        else                                       return z;
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(dec)(a);
      }
    }
    else  { return apply_over(saturated(prev), a);    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  // regular call
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        using i_t = as_integer_t<T>;
        return bitfloating(bitinteger(a) -  to_<i_t>(n));
      }
      else if constexpr(integral_value<T>)
      {
        return sub(a, to_<T>(n));
      }
    }
    else  { return apply_over(prev, a, n);    }
  }


  //////////////////////////////////////////////////////////////
  // pedantic call
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      ,  pedantic_type const &
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        using iT = as_integer_t<T>;
        auto nz = inc(bitinteger(a) -  to_<iT>(n));
        auto z  = bitfloating( dec(nz) );
        auto test = is_negative(z) && is_positive(a);
        if constexpr(scalar_value<T> && scalar_value<U>)
        {
          return test ? (nz == 0 ? T(-0.) : bitfloating(nz)) : z;
        }
        else
        {
          return if_else(test, if_else(is_eqz(nz), mzero(eve::as<T>()), bitfloating(nz)), z);
        }
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(sub)(a, to_<T>(n));
      }
    }
    else  { return apply_over(pedantic(prev), a, n);    }
  }



  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const &
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto z =  prev(a, n);
        if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits, z);
        else                                       return z;
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(sub)(a, to_<T>(n));
      }
    }
    else  { return apply_over(saturated(prev), a, n);    }
  }
}
