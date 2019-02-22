//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019  Jean-Thierry Lapreste
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_GREATER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_GREATER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_not.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/forward.hpp>
#include <eve/constant/true.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(simd_),
                                   wide<T, N, ABI> const &v0,
                                   U const &v1) noexcept requires(wide<logical<T>, N, ABI>,
                                                                  detail::Convertible<U, T>)
  {
    return eve::is_greater(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  is_greater_(EVE_SUPPORTS(simd_),
              U const &              v0,
              wide<T, N, ABI> const &v1) noexcept requires(wide<logical<T>, N, ABI>,
                                                           detail::Convertible<U, T>)
  {
    return eve::is_greater(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(simd_),
                                   wide<T, N, aggregated_> const &v0,
                                   wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::is_greater, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(simd_),
                                   wide<T, N, emulated_> const &v0,
                                   wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::is_greater, v0, v1);
  }
}

namespace eve
{
  // -----------------------------------------------------------------------------------------------
  // operator >
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator>(wide<T, N, ABI> const &v0, wide<T, N, ABI> const &v1) noexcept
  {
    return eve::is_greater(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator>(wide<T, N, ABI> const &v0,
                                 U const &v1) noexcept requires(wide<logical<T>, N, ABI>,
                                                                detail::Convertible<U, T>)
  {
    return eve::is_greater(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  operator>(U const &v0, wide<T, N, ABI> const &v1) noexcept requires(wide<logical<T>, N, ABI>,
                                                                      detail::Convertible<U, T>)
  {
    return eve::is_greater(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }
}

#endif
