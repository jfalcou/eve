//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> bitwise_and_(EVE_SUPPORTS(simd_),
                                                       wide<T, N, aggregated_> const &v0,
                                                       wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::bitwise_and, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto bitwise_and_(EVE_SUPPORTS(simd_),
                                    wide<T, N, emulated_> const &v0,
                                    wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::bitwise_and, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto bitwise_and_(EVE_SUPPORTS(simd_),
                                    wide<T, N, emulated_> const &v0,
                                    U const &v1) noexcept requires(wide<T, N, emulated_>,
                                                                   Convertible<U, T>)
  {
    return map(eve::bitwise_and, v0, T(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto
  bitwise_and_(EVE_SUPPORTS(simd_),
               U const &                    v0,
               wide<T, N, emulated_> const &v1) noexcept requires(wide<T, N, emulated_>,
                                                                  Convertible<U, T>)
  {
    return map(eve::bitwise_and, T(v0), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto bitwise_and_(EVE_SUPPORTS(simd_),
                                    wide<T, N, ABI> const &v0,
                                    U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                   Convertible<U, T>)
  {
    return eve::bitwise_and(v0, wide<T, N, ABI>(v1));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto bitwise_and_(EVE_SUPPORTS(simd_),
                                    U const &              v0,
                                    wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                                 Convertible<U, T>)
  {
    return eve::bitwise_and(wide<T, N, ABI>(v0), v1);
  }

  template<typename T, typename N, typename U, typename M>
  EVE_FORCEINLINE auto
  bitwise_and_(EVE_SUPPORTS(simd_), wide<U, M> const &v0, wide<T, N> const &v1) noexcept
  {
    return eve::bitwise_and(v0, bitwise_cast<wide<U, M>>(v1));
  }
}
// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T0, typename N0, typename T1, typename N1, typename ABI>
  EVE_FORCEINLINE auto operator&(wide<T0, N0, ABI> const &v0, wide<T1, N1, ABI> const &v1) noexcept
  {
    return eve::bitwise_and(v0, eve::bitwise_cast<wide<T0, N0, ABI>>(v1));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator&(wide<T, N, ABI> const &v0,
                                 U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                detail::Convertible<U, T>)
  {
    return eve::bitwise_and(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  operator&(U const &v0, wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                      detail::Convertible<U, T>)
  {
    return eve::bitwise_and(v0, v1);
  }
}

#endif
