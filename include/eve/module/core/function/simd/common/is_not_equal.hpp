//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve
{
  // -----------------------------------------------------------------------------------------------
  // operator !=
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto operator!=(  wide<T, N, ABI> const &v0,
                                    wide<T, N, ABI> const &v1) noexcept
  {
    return eve::is_not_equal(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator!=(wide<T, N, ABI> const &v0,
                                  U const &v1) noexcept requires(as_logical_t<wide<T, N, ABI>>,
                                                                 detail::Convertible<U, T>)
  {
    return eve::is_not_equal(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  operator!=(U const &v0, wide<T, N, ABI> const &v1) noexcept requires(as_logical_t<wide<T, N, ABI>>,
                                                                       detail::Convertible<U, T>)
  {
    return eve::is_not_equal(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }

  // -----------------------------------------------------------------------------------------------
  // operator != for logical<wide>
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator!=(logical<wide<T,N,ABI>> const &v0,
                                  logical<wide<T,N,ABI>> const &v1) noexcept
  {
    return bitwise_cast<logical<wide<T,N,ABI>>>( is_not_equal(v0.bits(),v1.bits()) );
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator!=(logical<wide<T,N,ABI>> const &v0,
                                  logical<U> const &v1) noexcept
                  requires(as_logical_t<wide<T, N, ABI>>, Scalar<U>)
  {
    return bitwise_cast<logical<wide<T,N,ABI>>>( is_not_equal(v0.bits(),v1.bits()) );
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto operator!=( logical<U> const &v0,
                                   logical<wide<T,N,ABI>> const &v1) noexcept
                  requires(as_logical_t<wide<T, N, ABI>>,Scalar<U>)
  {
    return bitwise_cast<logical<wide<T,N,ABI>>>( is_not_equal(v0.bits(),v1.bits()) );
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator!=(logical<wide<T,N,ABI>> const &v0,bool v1) noexcept
  {
    return logical<wide<T,N,ABI>>(v1) != v0;
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator!=( bool v0, logical<wide<T,N,ABI>> const &v1) noexcept
  {
    return logical<wide<T,N,ABI>>(v0) != v1;
  }
}

#endif
