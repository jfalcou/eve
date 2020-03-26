//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ACOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ACOSH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/add.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto acosh_(EVE_SUPPORTS(cpu_)
                                       , T x) noexcept
  requires std::floating_point<T>
  {
    T t = dec(x);
    if(t <= Oneotwoeps<T>())
      return eve::log1p(t+eve::sqrt(t+t+sqr(t)));
    else
      return eve::log(t)+Log_2<T>();
  }
}

#endif
