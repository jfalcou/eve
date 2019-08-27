//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IFNOT_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IFNOT_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto  ifnot_else_ ( EVE_SUPPORTS(cpu_),
                                                T const &cond,
                                                U const &t, V const &f
                                              ) noexcept
                  -> decltype(if_else(cond, f, t))
  {
    return if_else(cond, f, t);
  }
}

#endif
