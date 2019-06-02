//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITOFSIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITOFSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto bitofsign_(EVE_SUPPORTS(cpu_)
                                           , T const &a) noexcept
  requires(T, Vectorizable<T> )
  {
    return bitwise_and(a, Signmask(as(a))); 
  }
}

#endif
