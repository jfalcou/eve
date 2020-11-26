//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/scalar/load.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  // Arithmetic
  template<typename Size, typename T, typename ABI>
  EVE_FORCEINLINE auto load(T *ptr, as_<wide<T, Size, ABI>> const &) noexcept
  {
    return wide<T, Size>(ptr);
  }

  template<typename Size,typename ABI,typename T,std::size_t Align>
  EVE_FORCEINLINE auto load(aligned_ptr<T, Align> ptr, as_<wide<T, Size, ABI>> const &) noexcept
  requires(Align >= alignof(wide<T, Size>))
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

  template<typename Size,typename ABI,typename T,std::size_t Align>
  EVE_FORCEINLINE auto load(aligned_ptr<logical<T>, Align> ptr,
                            as_<logical<wide<T, Size, ABI>>> const &) noexcept
  requires(Align >= alignof(wide<T, Size>))
  {
    return logical<wide<T, Size, ABI>>(ptr);
  }
}

