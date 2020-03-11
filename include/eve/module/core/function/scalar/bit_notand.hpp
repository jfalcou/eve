//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_NOTAND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_NOTAND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/bit_and.hpp>
#include <eve/function/scalar/bit_not.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bit_notand_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires(T, vectorizable<T>, vectorizable<U>, bit_compatible<T,U>)
  {
    return bit_and(bit_not(a), b);
  }
}

#endif
