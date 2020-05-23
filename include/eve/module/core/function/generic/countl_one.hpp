//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_COUNTL_ONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_COUNTL_ONE_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

#include <bit>
#include <type_traits>

namespace eve::detail
{
  template<unsigned_value T> EVE_FORCEINLINE T countl_one_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return T(std::countl_one(v));
    }
    else if constexpr( has_native_abi_v<T> )
    {
      return map(countl_one, v); // TO DO
    }
    else
      return apply_over(countl_one, v);
  }
}

#endif
