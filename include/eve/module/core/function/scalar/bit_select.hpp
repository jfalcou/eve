//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bit_select_(EVE_SUPPORTS(cpu_),
                  T const &a0,
                  U const &a1,
                  U const &a2) noexcept
  Requires(U, Vectorizable<T>, Vectorizable<U>, bit_compatible<T,U>)
  {
    return eve::bit_or(eve::bit_and(a1, a0), eve::bit_andnot(a2, a0));
  }
}

#endif
