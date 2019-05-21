//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_ANDNOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_ANDNOT_HPP_INCLUDED

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
  EVE_FORCEINLINE wide<T, N, aggregated_>
                  bitwise_andnot_(EVE_SUPPORTS(simd_),
                                  wide<T, N, aggregated_> const &v0,
                                  wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::bitwise_andnot, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto bitwise_andnot_(EVE_SUPPORTS(simd_),
                                       wide<T, N, emulated_> const &v0,
                                       wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::bitwise_andnot, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto bitwise_andnot_(EVE_SUPPORTS(simd_),
                                       wide<T, N, emulated_> const &v0,
                                       U const &v1) noexcept requires(wide<T, N, emulated_>,
                                                                      Convertible<U, T>)
  {
    return map(eve::bitwise_andnot, v0, T(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto
  bitwise_andnot_(EVE_SUPPORTS(simd_),
                  U const &                    v0,
                  wide<T, N, emulated_> const &v1) noexcept requires(wide<T, N, emulated_>,
                                                                     Convertible<U, T>) = delete;

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto bitwise_andnot_(EVE_SUPPORTS(simd_),
                                       wide<T, N, ABI> const &v0,
                                       U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                      Convertible<U, T>)
  {
    return eve::bitwise_andnot(v0, wide<T, N, ABI>(v1));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  bitwise_andnot_(EVE_SUPPORTS(simd_),
                  U const &              v0,
                  wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                               Convertible<U, T>) = delete;

  template<typename T, typename N, typename U, typename M>
  EVE_FORCEINLINE auto
  bitwise_andnot_(EVE_SUPPORTS(simd_), wide<U, M> const &v0, wide<T, N> const &v1) noexcept
  {
    return eve::bitwise_andnot(v0, bitwise_cast<wide<U, M>>(v1));
  }
}

#endif
