//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_NONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_NONE_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_)
                           , T const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return !v;
    }
    else if constexpr(simd_value<T>)
    {
      return !any(v);
    }
  }
}

#endif
