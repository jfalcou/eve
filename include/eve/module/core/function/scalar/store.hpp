//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE auto
  store_(EVE_SUPPORTS(cpu_), T value, T *ptr) noexcept requires(void, Vectorizable<T>)
  {
    *ptr = value;
  }

  // -----------------------------------------------------------------------------------------------
  // Aligned case
  template<typename T, std::size_t N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_),
                              T                 value,
                              aligned_ptr<T, N> ptr) noexcept requires(void, Vectorizable<T>)
  {
    *ptr = value;
  }
}

#endif
