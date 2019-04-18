//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_MASK_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_MASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T bitwise_mask_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return is_nez(a0).mask();
  }

  // -----------------------------------------------------------------------------------------------
  // logical case
  template<typename T>
  EVE_FORCEINLINE constexpr T bitwise_mask_(EVE_SUPPORTS(cpu_), logical<T> const &a0) noexcept
  {
    return a0.mask();
  }

  // -----------------------------------------------------------------------------------------------
  // bool case is forbidden as we can't go back to a properly sized mask
  EVE_FORCEINLINE constexpr bool bitwise_mask_(EVE_SUPPORTS(cpu_), bool a0) noexcept = delete;
}

#endif
