//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TWO_SPLIT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TWO_SPLIT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto two_split_(EVE_SUPPORTS(cpu_)
                                 , const T& a) noexcept
  {
    //enforce_precision<T> enforcer;
    T const c = Ieee_constant<value_type_t<T>, 0x46000000U, 0x41a0000000000000ULL>()*a;
    T const c1 = c-a;
    T r0 = c-c1;
    return std::make_tuple(r0, a-r0); 
   }

}

#endif
