//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE auto
  shl_(EVE_SUPPORTS(simd_), wide<T, N, aggregated_> const &v0, U const &v1) noexcept
  {
    return aggregate(eve::shl, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE auto
  shl_(EVE_SUPPORTS(simd_), wide<T, N, emulated_> const &v0, U const &v1) noexcept
  {
    return map(eve::shl, v0, v1);
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto operator<<(wide<T, N, ABI> const &v0, wide<U, N, ABI> const &v1) noexcept
  {
    return eve::shl(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator<<(wide<T, N, ABI> const &v0,
                                 U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                detail::Convertible<U, T>)
  {
    return eve::shl(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  operator<<(U const &v0, wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                      detail::Convertible<U, T>)
  {
    return eve::shl(v0, v1);
  }
}
#endif
