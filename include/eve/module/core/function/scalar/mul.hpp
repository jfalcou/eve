//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto mul_(EVE_SUPPORTS(cpu_)
                                     , T const &a
                                     , T const &b) noexcept
  requires(T, Vectorizable<T>)
  {
    return a*b;
  }
}

#endif

#include "if_mul.hpp"
