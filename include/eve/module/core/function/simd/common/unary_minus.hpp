//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_UNARY_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_UNARY_MINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> unary_minus_(EVE_SUPPORTS(cpu_),
                                               wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_native_v<ABI>)
    {
      if (std::is_floating_point_v<value_type_t<T>>)
      {
        return  bit_xor(v, Signmask(as(v))); 
      }
      else
      {
        return Zero(as(v)) - v;
      }
    }
    else
    {
      if constexpr(is_aggregated_v<ABI>) return aggregate(eve::unary_minus, v);
      if constexpr(is_emulated_v<ABI>) return map(eve::unary_minus, v);
    }
  }
  
 // -----------------------------------------------------------------------------------------------
  // Conditionnal
  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> unary_minus_(EVE_SUPPORTS(cpu_),
                                               U const & cond, 
                                               wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_vectorizable_v<U>)
      return cond ? unary_minus(v) : v;
    else
      return if_else(cond, unary_minus(v), v); 
  }

}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator-(wide<T, N, ABI> const &v) noexcept
  {
    return unary_minus(v);
  }
}

#endif
