//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_ORDERED_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_ORDERED_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_ordered_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept Requires(as_logical_t<T>,
                                                                            Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return (a == a) && (b == b);
    else
      return true;
  }
}

#endif
