//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  logical_xor_(EVE_SUPPORTS(simd_), wide<T, N, ABI> const &v0, wide<T, N, ABI> const &v1) noexcept
  {
    return eve::bitwise_cast<wide<logical<T>, N, ABI>>(
        eve::bitwise_xor(eve::bitwise_mask(v0), eve::bitwise_mask(v1)));
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(simd_),
                                    wide<T, N, ABI> const &v0,
                                    U const &v1) noexcept requires(wide<logical<T>, N, ABI>,
                                                                   detail::Convertible<U, T>)
  {
    return eve::logical_xor(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  logical_xor_(EVE_SUPPORTS(simd_),
               U const &              v0,
               wide<T, N, ABI> const &v1) noexcept requires(wide<logical<T>, N, ABI>,
                                                            detail::Convertible<U, T>)
  {
    return eve::logical_xor(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(simd_),
                                    wide<T, N, aggregated_> const &v0,
                                    wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::logical_xor, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(simd_),
                                    wide<T, N, emulated_> const &v0,
                                    wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::logical_xor, v0, v1);
  }
}


#endif
