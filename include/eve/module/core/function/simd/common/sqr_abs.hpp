//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SQR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SQR_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto sqr_abs_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &a0) noexcept
  {
    return sqr(a0); 
  }
  

  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr T sqr_abs_(EVE_SUPPORTS(simd_)
                                  ,saturated_type const & 
                                  , wide<T, N, ABI> const &a0) noexcept
  {
    return sqr[saturated_>(a0); 
  }  
}

#endif
  
