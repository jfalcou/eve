//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> unary_minus_(EVE_SUPPORTS(simd_),
                                               wide<T, N, ABI> const &v) noexcept
  {
   if constexpr( is_native_v<ABI> )
    {
      return Zero(as(v)) - v;
    }
    else
    {
      if constexpr( is_aggregated_v<ABI> ) return aggregate(eve::unary_minus, v);
      if constexpr( is_emulated_v<ABI>   ) return map(eve::unary_minus, v);
    }   
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
