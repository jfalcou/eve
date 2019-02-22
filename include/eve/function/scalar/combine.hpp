//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SCALAR_COMBINE_HPP_INCLUDED
#define EVE_FUNCTION_SCALAR_COMBINE_HPP_INCLUDED

#include <eve/function/definition/combine.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/wide.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto combine_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    return wide<T, fixed<2>>(a, b);
  }
}

#endif
