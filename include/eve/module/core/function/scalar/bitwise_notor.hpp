//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_NOTOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_NOTOR_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/scalar/bitwise_not.hpp>
#include <eve/function/scalar/bitwise_or.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr T bitwise_notor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    static_assert(sizeof(T) == sizeof(U), "eve::bitwise_notor - Arguments have incompatible size");
    return eve::bitwise_or(eve::bitwise_not(a), b);
  }
}

#endif
