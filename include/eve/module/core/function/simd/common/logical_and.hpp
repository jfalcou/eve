//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve
{
  // -----------------------------------------------------------------------------------------------
  // operator && - wide
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator&&(wide<T, N, ABI> const &v0, wide<T, N, ABI> const &v1) noexcept
  {
    return eve::logical_and(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator&&(wide<T, N, ABI> const &v0,
                                  U const &v1) noexcept requires(as_logical_t<wide<T, N, ABI>>,
                                                                 detail::Convertible<U, T>)
  {
    return eve::logical_and(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  operator&&(U const &v0, wide<T, N, ABI> const &v1) noexcept requires(as_logical_t<wide<T, N, ABI>>,
                                                                       detail::Convertible<U, T>)
  {
    return eve::logical_and(v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // operator && - logical
  template<typename T>
  EVE_FORCEINLINE auto operator&&(logical<T> const &v0, logical<T> const &v1) noexcept
  {
    return eve::logical_and(v0, v1);
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto operator&&(logical<T> const &v0,
                                  U const &v1) noexcept requires(as_logical_t<T>,
                                                                 Scalar<U>)
  {
    return eve::logical_and(v0, v1);
  }

  template<typename T, typename U>
  EVE_FORCEINLINE auto
  operator&&(U const &v0, logical<T> const &v1) noexcept requires(as_logical_t<T>,
                                                                       Scalar<U>)
  {
    return eve::logical_and(v0, v1);
  }
}

#endif
