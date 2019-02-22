//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_NOTOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_NOTOR_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_not.hpp>
#include <eve/function/bitwise_or.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Native
  template<typename T, typename N, typename API>
  EVE_FORCEINLINE wide<T, N, API>
                  bitwise_notor_(EVE_SUPPORTS(simd_), wide<T, N, API> const &v0, wide<T, N, API> const &v1) noexcept
  {
    return eve::bitwise_or(bitwise_not(v0), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> bitwise_notor_(EVE_SUPPORTS(simd_),
                                                         wide<T, N, aggregated_> const &v0,
                                                         wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::bitwise_notor, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto bitwise_notor_(EVE_SUPPORTS(simd_),
                                      wide<T, N, emulated_> const &v0,
                                      wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::bitwise_notor, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto bitwise_notor_(EVE_SUPPORTS(simd_),
                                      wide<T, N, emulated_> const &v0,
                                      U const &v1) noexcept requires(wide<T, N, emulated_>,
                                                                     Convertible<U, T>)
  {
    return map(eve::bitwise_notor, v0, T(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto
  bitwise_notor_(EVE_SUPPORTS(simd_),
                 U const &                    v0,
                 wide<T, N, emulated_> const &v1) noexcept requires(wide<T, N, emulated_>,
                                                                    Convertible<U, T>) =  delete; 


  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T0, typename N0, typename T1, typename N1, typename ABI>
  EVE_FORCEINLINE auto bitwise_notor(wide<T0, N0, ABI> const &v0
                                    , wide<T1, N1, ABI> const &v1) noexcept
  {
    return eve::bitwise_and(v0, eve::bitwise_cast<wide<T0, N0, ABI>>(v1));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto bitwise_notor_(EVE_SUPPORTS(simd_),
                                      wide<T, N, ABI> const &v0,
                                      U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                     Convertible<U, T>)
  {
    return eve::bitwise_notor(v0, wide<T, N, ABI>(v1));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  bitwise_notor_(EVE_SUPPORTS(simd_),
                 U const &              v0,
                 wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>, Convertible<U, T>) =  delete; 

}

#endif
