//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  
  template<typename T,  typename Tag>
  EVE_FORCEINLINE auto sec_(EVE_SUPPORTS(cpu_)
                           , Tag const &
                           , T a0) noexcept
  requires(T,  vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return rec(Tag()(cos)(a0)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sec generic ] - type is not an IEEEValue"); 
    }   
  }
  
  template<typename T>
  EVE_FORCEINLINE auto sec_(EVE_SUPPORTS(cpu_)
                           , T const &a0) noexcept
  requires(T,  vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      return rec(cos(a0)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "[eve::sec generic ] - type is not an IEEEValue"); 
    }   
  }
}

#endif
