//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_POW_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_POW_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>  
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T, typename U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_)
                               , T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point,T>,
            floating_point<value_type_t<U>>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return pow(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return pow(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        auto nega = is_negative(a);
        T z = pow_abs(a, b);
        z =  unary_minus[logical_and(is_odd(b), nega)](z); //neg[logical_and(is_odd(b), nega)](z);
        auto invalid =  logical_andnot(nega, logical_or(is_flint(b), is_infinite(b)));
        return if_else(invalid, eve::allbits_, z);
      }
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(cpu_)
                               , raw_type const &
                               , T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point,T>,
            floating_point<value_type_t<U>>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return pow_abs(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return pow_abs(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        return exp(b*log(a)); 
      }
    }
  } 
}

#endif
