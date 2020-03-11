//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SEC_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/wide.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T,  typename N,  typename ABI, typename Tag>
  EVE_FORCEINLINE auto sec_(EVE_SUPPORTS(cpu_)
                           , Tag const &  
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return rec(Tag()(eve::cos)(a0)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sec simd ] - type is not an IEEEValue"); 
    }   
  }

 

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto sec_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    return rec(eve::cos(a0));
  }
}

#endif
