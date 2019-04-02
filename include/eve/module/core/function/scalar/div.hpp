//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto div_(EVE_SUPPORTS(cpu_)
                                     , T const &a
                                     , T const &b) noexcept requires(T, Arithmetic<T>)
  {
    if constexpr(!std::is_floating_point_v<T>)
      EVE_ASSERT(b, "[eve::div ] - you cannot divide by 0 with integral types.");
    return a/b;
  }
 
}

#endif
