//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // if  zero else one
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , callable_object<eve::tag::zero_>
          , callable_object<eve::tag::one_>
          ) noexcept
  {
    return bitwise_notand((bitwise_mask(v0), One(as(v0))));
  }
  
}

#endif
