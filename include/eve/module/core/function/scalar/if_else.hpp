//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr
  auto  if_else_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, U const &f) noexcept
        requires( U, Vectorizable<T> )
  {
    return static_cast<bool>(cond) ? t : f;
  }
}

#endif
