//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SCALAR_LOAD_HPP_INCLUDED
#define EVE_FUNCTION_SCALAR_LOAD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>

namespace eve
{
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
}

#endif
