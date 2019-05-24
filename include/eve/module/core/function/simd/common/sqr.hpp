//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SQR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SQR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/mul.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/sqrtvalmax.hpp>    
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto sqr_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &a0) noexcept
  {
    return a0*a0; 
  }
  

  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr T sqr_(EVE_SUPPORTS(simd_)
                                  ,saturated_type const & 
                                  , wide<T, N, ABI> const &a0) noexcept
  {
    if (std::is_integral_v<T>)
    {
      if constexpr(std::is_signed_v<T>)
        return if_else(abs[eve::saturated_](a0) > Sqrtvalmax(as(a0)), Valmax(as(a0)), sqr(a0));
      else
        return if_else((a0 > Sqrtvalmax(as(a0))), Valmax(as(a0)), sqr(a0));
    }          
    else
      return sqr(a0);
  }  
}

#endif
  
