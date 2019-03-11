//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // if one else zero
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , callable_object<eve::tag::one_>
          , callable_object<eve::tag::zero_>
          ) noexcept
  {
    if constexpr(std::is_integral_v<U>)
      return bitwise_and(bitwise_mask(v0), One(as(v0)));
    else
      return if_else(v0, One(as(v0)), Zero(as(v0))); 
  }
  
}

#endif
