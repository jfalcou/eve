//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOGICAL_OR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOGICAL_OR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  logical_or_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(as_logical_t<T>,
                                                                            vectorizable<T>,
                                                                            vectorizable<U>)
  {
    if constexpr(is_logical_v<T> || is_logical_v<U>)
    { return static_cast<bool>(a) || static_cast<bool>(b); }
    else
    {
      return a || b;
    }
  }
}

namespace eve
{
  // -----------------------------------------------------------------------------------------------
  // operator &&
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator||(T const &a, U const &b) noexcept
      -> decltype(eve::logical_or(a, b))
  {
    return eve::logical_or(a, b);
  }
}

#endif
