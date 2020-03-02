//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_POW_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_POW_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>  
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
          , T const &a0, T const &a1) noexcept
  requires(T, floating_point<T>)
  {
    auto ltza0 = is_ltz(a0);
    auto isinfa1 = is_infinite(a1);
    if( a0 == Mone<T>() && isinfa1 ) return One<T>();
    if( ltza0 && !is_flint(a1) && !is_infinite(a1) ) return Nan<T>();
    auto z = pow_abs(a0, a1);
    if (isinfa1) return z;
    return (is_negative(a0) && is_odd(a1)) ? -z : z;
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
          , raw_type const &
          , T const &a0, T const &a1) noexcept
  requires(T, floating_point<T>)
  {
    return exp(a1*log(a0)); 
  } 
}

#endif
