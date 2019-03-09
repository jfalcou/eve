//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr as_logical_t<T>
  is_equal_with_equal_nans_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    if constexpr(std::is_floating_point_v<T> && std::is_floating_point_v<U>)
      return (a == b) || ((a!= a) && (b!= b));
    else
      return (a == b); 
  }
}

#endif
