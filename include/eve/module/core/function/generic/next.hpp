//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_NEXT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_NEXT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/add.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  ////////////////////////////////////////////////
  // saturated_
  template<typename T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const & _
                                      , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto z =  bitfloating(saturated_(inc)(bitinteger(a)));
      z = if_else (is_negative(a) && is_positive(z), prev(z), z); 
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
      return saturated_(inc)(a);
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const & 
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      using i_t = as_integer_t<value_type_t<T>>; 
      auto z =  bitfloating(saturated_(add)(bitinteger(a), convert(n, as<i_t>()))); 
      z = if_else (is_negative(a) && is_positive(z), prev(z), z); 
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
      return saturated_(add)(a, convert(n, as<value_type_t<T>>()));
    }
  }
  
  //////////////////////////////////////////////////////////////
  // regular call
  template<typename T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto z =  bitfloating(inc(bitinteger(a))); 
      z = if_else (is_negative(a) && is_positive(z), prev(z), z); 
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
      return inc(a);
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      using i_t = as_integer_t<value_type_t<T>>; 
      auto z =  bitfloating(add(bitinteger(a), convert(n, as<i_t>()))); 
      z = if_else (is_negative(a) && is_positive(z), prev(z), z); 
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
      return add(a, convert(n, as<value_type_t<T>>()));
    }
  }
}

#endif
