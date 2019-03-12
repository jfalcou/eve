//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_ONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_ONE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/function/bitwise_ornot.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // if else one 
  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , wide<U, N, ABI> const &v1
          , callable_object<eve::tag::one_>) noexcept
  {
    if constexpr(std::is_integral_v<U>)
      return -bitwise_ornot(-v1, bitwise_mask(v0));
    else
      return if_else(v0, v1, One(as(v1))); 
  }


  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , T const &v1
          , eve::callable_one_ 
          ) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    if constexpr(std::is_integral_v<T>)
      return -bitwise_ornot(t_t(-v1), bitwise_mask(v0));
    else
      return if_else(v0, v1, One<t_t>()); 
  }
 
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<logical<T>, N, ABI> const &v0
          , T const &v1
          , eve::callable_one_
          ) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    if constexpr(std::is_integral_v<T>)
      return -bitwise_ornot(t_t(-v1), bitwise_mask(v0));
    else
      return if_else(v0, t_t(v1), One<t_t>()); 
  } 
  
}

#endif
