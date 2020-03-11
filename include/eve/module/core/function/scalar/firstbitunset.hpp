//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FIRSTBITUNSET_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FIRSTBITUNSET_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto firstbitunset_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  requires(T, integral<T>)
  {
    return ~a0 & (a0+One(as(a0)));
  }
}

#endif
