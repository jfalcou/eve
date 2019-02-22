//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_MASK_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_MASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto bitwise_mask_(EVE_SUPPORTS(simd_),
                                     wide<T, N, ABI> const &v) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    return bitwise_cast<t_t>(is_nez(v));
  }
  // -----------------------------------------------------------------------------------------------
  // logical
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto bitwise_mask_(EVE_SUPPORTS(simd_),
                                     wide<logical<T>, N, ABI> const &v) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    return bitwise_cast<t_t>(v);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> bitwise_mask_(EVE_SUPPORTS(simd_),
                                                       wide<T, N, aggregated_> const &v) noexcept
  {
    return aggregate(eve::bitwise_mask, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto bitwise_mask_(EVE_SUPPORTS(simd_), wide<T, N, emulated_> const &v0) noexcept
  {
    return map(eve::bitwise_mask, v0);
  }
}

#endif
