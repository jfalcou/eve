//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_LOAD_HPP_INCLUDED
#define EVE_FUNCTION_LOAD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  // SCALAR
  //================================================================================================
  template<typename T>
  EVE_FORCEINLINE auto load(T *ptr) noexcept
  {
    return *ptr;
  }

  template<typename T, std::size_t Align>
  EVE_FORCEINLINE auto load(aligned_ptr<T, Align> ptr) noexcept
  {
    return *ptr;
  }

  template<typename T>
  EVE_FORCEINLINE auto load(T *ptr, as_<T> const &) noexcept
  {
    return *ptr;
  }

  template<typename T, std::size_t Align, typename = std::enable_if_t<(Align >= alignof(T))>>
  EVE_FORCEINLINE auto load(aligned_ptr<T, Align> ptr, as_<T> const &) noexcept
  {
    return *ptr;
  }

  //================================================================================================
  // SIMD
  //================================================================================================
  // Arithmetic
  template<typename T, typename Size, typename ABI>
  EVE_FORCEINLINE auto load(wide<T, Size, ABI> *ptr) noexcept
  {
    return *ptr;
  }

  template<typename T, typename Size, typename ABI>
  EVE_FORCEINLINE auto load(aligned_ptr<wide<T, Size, ABI>> ptr) noexcept
  {
    return *ptr;
  }

  template<typename Size, typename T, typename ABI>
  EVE_FORCEINLINE auto load(T *ptr, as_<wide<T, Size, ABI>> const &) noexcept
  {
    return wide<T, Size>(ptr);
  }

  template<typename Size,
           typename ABI,
           typename T,
           std::size_t Align,
           typename = std::enable_if_t<(Align >= wide<T, Size>::static_alignment)>>
  EVE_FORCEINLINE auto load(aligned_ptr<T, Align> ptr, as_<wide<T, Size, ABI>> const &) noexcept
  {
    return wide<T, Size>(ptr);
  }

  //================================================================================================
  // Logical
  template<typename Size, typename T, typename ABI>
  EVE_FORCEINLINE auto load(logical<T> *ptr, as_<logical<wide<T, Size, ABI>>> const &) noexcept
  {
    return logical<wide<T, Size>>(ptr);
  }

  template<typename Size,
           typename ABI,
           typename T,
           std::size_t Align,
           typename = std::enable_if_t<(Align >= wide<T, Size>::static_alignment)>>
  EVE_FORCEINLINE auto load(aligned_ptr<logical<T>, Align> ptr,
                            as_<logical<wide<T, Size, ABI>>> const &) noexcept
  {
    return logical<wide<T, Size, ABI>>(ptr);
  }
}

#endif
