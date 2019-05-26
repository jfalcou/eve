//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SQR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SQR_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T sqr_abs_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    return sqr(a); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr T sqr_abs_(EVE_SUPPORTS(simd_)
                                  , saturated_type const & 
                                  , T const &a0) noexcept
  {
    return sqr[saturated_](a0);
  } 
}

#endif
  
