//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_PREV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_PREV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/all.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  ////////////////////////////////////////////////
  // saturated_
  template<typename T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const & _
                                      , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto z =  bitfloating(saturated_(dec)(bitinteger(a))); 
      if constexpr(eve::platform::supports_nans)
      {
        return if_else(is_nan(a), eve::allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<value_type_t<T>>)
    {
      return saturated_(dec)(a);
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const & 
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(!std::is_integral_v<value_type_t<U>>)
    {
      static_assert(std::is_integral_v<value_type_t<U>>, "[prev] : second parameter must be of integral type");
    }
    else if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      EVE_ASSERT(all(is_gez(n)), "[prev] : second parameter must be positive");
      auto z =  bitfloating(saturated_(sub)(bitinteger(a), n)); 
      if constexpr(eve::platform::supports_nans)
      {
        return if_else(is_nan(a), eve::allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      return saturated_(sub)(a, n);
    }
  }
  
  //////////////////////////////////////////////////////////////
  // regular call
  template<typename T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto z =  bitfloating(dec(bitinteger(a))); 
      if constexpr(eve::platform::supports_nans)
      {
        return if_else(is_nan(a), eve::allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<value_type_t<T>>)
    {
      return dec(a);
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
   if constexpr(!std::is_integral_v<value_type_t<U>>)
    {
      static_assert(std::is_integral_v<value_type_t<U>>, "[prev] : second parameter must be of integral type");
    }
    else if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      EVE_ASSERT(all(is_gez(n)), "[prev] : second parameter must be positive");
      auto z =  bitfloating(sub(bitinteger(a), n)); 
      if constexpr(eve::platform::supports_nans)
      {
        return if_else(is_nan(a), eve::allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      return sub(a, n);
    }
  }
}

#endif
