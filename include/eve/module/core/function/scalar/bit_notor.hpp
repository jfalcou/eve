//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_NOTOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_NOTOR_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_or.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bit_notor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  Requires(T, Vectorizable<T>, Vectorizable<U>, Bit_compatible<T,U>)
  {
    return eve::bit_or(eve::bit_not(a), b);
  }
}

#endif
