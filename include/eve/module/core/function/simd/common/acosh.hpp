//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_ACOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_ACOSH_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto acosh_(EVE_SUPPORTS(cpu_)
                            , const T &x) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    T t = dec(x);
    auto test = is_greater(t,Oneotwoeps<T>());
    T z = if_else(test, x, t+sqrt(t+t+sqr(t)));
    return add[test](log1p(z), Log_2<T>());    
  }
}

#endif

