//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SHL_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE  auto shl_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &a1) noexcept
  {
    if constexpr(scalar_value<T> && scalar_value<U>)
    {
      return static_cast<T>(a0 << a1);
    }
    else if (has_emulated_abi_v<T> || has_emulated_abi_v<U>)
    {
      return map(eve::shl, a0, a1);
    }
    else if constexpr(has_aggregated_abi_v<T> || has_aggregated_abi_v<U>)
    {
      return aggregate(eve::shl, a0, a1);
    }
    else
    {
      return map(eve::shl, a0, a1);
    }
  }
}

#endif
