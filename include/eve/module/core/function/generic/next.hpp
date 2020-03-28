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
#include <eve/function/add.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/add.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  //////////////////////////////////////////////////////////////
  // regular call
  template<real_value T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(floating_value<T>)
    {
      return bitfloating(inc(bitinteger(a))); 
    }
    else if constexpr(integral_value<T>)
    {
      return inc(a); 
    }
  }
  
  //////////////////////////////////////////////////////////////
  // pedantic call
  template<real_value T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , pedantic_type const & 
                                      , T const &a) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto pz = bitinteger(a); 
      auto z  = bitfloating( inc(pz) );
      auto test = is_negative(a) && is_positive(z);
      if constexpr(scalar_value<T>)
      {
        return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
      }
      else
      {
        return if_else(test, if_else(is_eqz(z), Mzero<T>(), bitfloating(pz)), z);
      }
    }
    else if constexpr(integral_value<T>)
    {
      return saturated_(inc)(a); 
    }
  }
  
  ////////////////////////////////////////////////
  // saturated_ call
  template< real_value T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const & 
                                      , T const &a) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto z =  next(a); 
      if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits_, z);
      else                                       return z;
    }
    else if constexpr(integral_value<T>)
    {
      return saturated_(inc)(a);
    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  // regular call
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(floating_value<T>)
    {
      using i_t = as_integer_t<value_type_t<T>>; 
      return bitfloating(bitinteger(a)+  convert(n, as<i_t>()));
    }
    else if constexpr(integral_value<T>)
    {
      return add(a, convert(n, as<value_type_t<T>>()));
    }
  }
  //////////////////////////////////////////////////////////////
  // pedantic_ call
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                     ,  pedantic_type const & 
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(floating_value<T>)
    {
      using i_t = as_integer_t<value_type_t<T>>; 
      auto pz = dec(bitinteger(a) +  convert(n, as<i_t>()));
      auto z  = bitfloating( inc(pz) );
      auto test = is_negative(a) && is_positive(z);
      if constexpr(scalar_value<T> && scalar_value<U>)
      {
        return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
      }
      else
      {
        return if_else(test, if_else(is_eqz(z), Mzero<T>(), bitfloating(pz)), z);
      }
    }
    else if constexpr(integral_value<T>)
    {
      return saturated_(add)(a, convert(n, as<value_type_t<T>>()));
    }
  }


  template<real_value T, integral_value U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , saturated_type const & 
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto z =  next(a, n); 
      if constexpr(eve::platform::supports_nans) return if_else(is_nan(a), eve::allbits_, z);
      else                                       return z;
    }
    else if constexpr(integral_value<T>)
    {
      return saturated_(add)(a, convert(n, as<value_type_t<T>>()));
    }
  }
}

#endif
