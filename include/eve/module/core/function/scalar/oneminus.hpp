//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ONEMINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ONEMINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  {
    return static_cast<T>(One<T>()-a); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(simd_)
                                     , U const & cond
                                     , T const &a) noexcept
  {
    return cond ? oneminus(a) : a;
  } 
}

#endif
