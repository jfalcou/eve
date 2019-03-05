//==================================================================================================
/**  
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_FINITE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_FINITE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/forward.hpp> 
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_not_finite_(EVE_SUPPORTS(simd_),
                               wide<T, N, ABI> const &v0) noexcept
  {
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>)
    {
      using t_t =  wide<as_logical_t<T>, N, ABI>; 
      return False<t_t>();
    }
    else 
      return is_nan(v0-v0);
  }
 
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_not_finite_(EVE_SUPPORTS(simd_),
                               wide<T, N, aggregated_> const &v0) noexcept
  {
    return aggregate(eve::is_not_finite, v0);
  }
  
  // -----------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_not_finite_(EVE_SUPPORTS(simd_),
                               wide<T, N, emulated_> const &v0) noexcept
  {
    return map(eve::is_not_finite, v0);
  }
}

#endif
