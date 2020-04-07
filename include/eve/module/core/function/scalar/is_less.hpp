//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_LESS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_LESS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/is_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  is_less_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept Requires(as_logical_t<T>,
                                                                         Vectorizable<T>,
                                                                         Vectorizable<U>)
  {
    if constexpr(is_logical_v<T> || is_logical_v<U>)
    { return static_cast<bool>(a) < static_cast<bool>(b); }
    else
    {
      return a < b;
    }
  }
}

#endif
