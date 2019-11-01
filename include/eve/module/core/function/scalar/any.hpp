//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ANY_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ANY_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto any_(EVE_SUPPORTS(cpu_),
                                      T const &a) noexcept
  requires(bool, vectorizable<T>)
  {
    return a;
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto any_(EVE_SUPPORTS(cpu_),
                                      logical<T> const &a) noexcept
  requires(bool, vectorizable<T>)
  {
    return a;
  }
}

#endif
