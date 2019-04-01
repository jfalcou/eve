//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/is_wide.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic for no simd present
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto mul_ ( EVE_SUPPORTS(simd_)
                                , wide<T, N, ABI> const& v0
                                , wide<T, N, ABI> const& v1
                                ) noexcept
  {
    if constexpr( std::is_same_v<ABI,aggregated_> )
       return aggregate( eve::mul, v0, v1);
    else
      return map( eve::mul, v0, v1);
  }
  
  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v0,
                            U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                           detail::Convertible<U, T>)
  {
    return eve::mul(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(simd_),
                            U const &              v0,
                            wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                         detail::Convertible<U, T>)
  {
    return eve::mul(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> mul_(EVE_SUPPORTS(simd_),
                                               wide<T, N, aggregated_> const &v0,
                                               wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::mul, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(simd_),
                            wide<T, N, emulated_> const &v0,
                            wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::mul, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(simd_),
                            wide<T, N, emulated_> const &v0,
                            U const &v1) noexcept requires(wide<T, N, emulated_>,
                                                           detail::Convertible<U, T>)
  {
    return map(eve::mul, v0, static_cast<T>(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto
  mul_(EVE_SUPPORTS(simd_),
       U const &                    v0,
       wide<T, N, emulated_> const &v1) noexcept requires(wide<T, N, emulated_>,
                                                          detail::Convertible<U, T>)
  {
    return map(eve::mul, static_cast<T>(v0), v1);
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator*(wide<T, N, ABI> const &v0, wide<T, N, ABI> const &v1) noexcept
  {
    return eve::mul(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator*(wide<T, N, ABI> const &v0,
                                 U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                detail::Convertible<U, T>)
  {
    return eve::mul(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  operator*(U const &v0, wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                      detail::Convertible<U, T>)
  {
    return eve::mul(v0, v1);
  }
}

#endif
