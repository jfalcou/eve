//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/assert.hpp>
#include <cstring>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE T bitwise_cast_(EVE_SUPPORTS(cpu_), T const &a, as_<T> const &) noexcept
  {
    return a;
  }

  template<typename T, typename Target>
  EVE_FORCEINLINE Target bitwise_cast_(EVE_SUPPORTS(cpu_), T const &a, as_<Target> const &) noexcept
  {
    EVE_ASSERT(sizeof(a) == sizeof(Target),
               "[ eve::bitwise_cast scalar] - Size mismatch in bitwise_cast " << sizeof(a) << " != " << sizeof(Target) << ".");
//    static_assert(sizeof(a) == sizeof(Target), "[eve] Size mismatch in bitwise_cast");

    Target that;
    std::memcpy(&that, &a, sizeof(a));
    return that;
  }
}

#endif
