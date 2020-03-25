//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto all_(EVE_SUPPORTS(cpu_),
                                      T const &a) noexcept
  Requires(bool, Vectorizable<T>)
  {
    return a;
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto all_(EVE_SUPPORTS(cpu_),
                                      logical<T> const &a) noexcept
  Requires(bool, Vectorizable<T>)
  {
    return a;
  }
}

#endif
