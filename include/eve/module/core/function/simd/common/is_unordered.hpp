//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_UNORDERED_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_UNORDERED_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/constant/false.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE wide<as_logical_t<T>, N, ABI> is_unordered_(EVE_SUPPORTS(simd_),
                                                              wide<T, N, ABI> const &v0,
                                                              wide<T, N, ABI> const &v1) noexcept
  {
    using t_t =  wide<as_logical_t<T>, N, ABI>;
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>)
      return False<t_t>();
    else
      return logical_or(is_not_equal(v0, v0), is_not_equal(v1, v1));
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto is_unordered_(EVE_SUPPORTS(simd_),
                                     wide<T, N, ABI> const &v0,
                                     U const &v1) noexcept requires(as_logical_t<wide<T, N, ABI>>,
                                                                    detail::Convertible<U, T>)
  {
    return eve::is_unordered(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  is_unordered_(EVE_SUPPORTS(simd_),
                U const &              v0,
                wide<T, N, ABI> const &v1) noexcept requires(as_logical_t<wide<T, N, ABI>>,
                                                             detail::Convertible<U, T>)
  {
    return eve::is_unordered(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_unordered_(EVE_SUPPORTS(simd_),
                                     wide<T, N, aggregated_> const &v0,
                                     wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::is_unordered, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_unordered_(EVE_SUPPORTS(simd_),
                                     wide<T, N, emulated_> const &v0,
                                     wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::is_unordered, v0, v1);
  }
}

#endif
