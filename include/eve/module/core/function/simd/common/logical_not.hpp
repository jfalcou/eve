//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_not.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/as_logical.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <type_traits>
 
namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(simd_),
                                    wide<T, N, ABI> const &v) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    return eve::is_equal(v, eve::Zero<t_t>());
  }
  
  // -----------------------------------------------------------------------------------------------
  // logical
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(simd_),
                                    as_logical_t<wide<T, N, ABI>> const &v) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    using l_t = as_logical_t<t_t>; 
    return eve::bitwise_cast<l_t>(eve::bitwise_not(eve::bitwise_cast<t_t>(v)));
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(simd_),
                                    wide<T, N, aggregated_> const &v) noexcept
  {
    return aggregate(eve::logical_not, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(simd_)
                                   , wide<T, N, emulated_> const &v0) noexcept
  {
    return map(eve::logical_not, v0);
  }
  
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator!(wide<T, N, ABI> const &v) noexcept
  {
    return eve::logical_not(v); 
  }
}

#endif
