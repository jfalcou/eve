//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MODF_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MODF_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/zero.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto modf_(EVE_SUPPORTS(cpu_),
                                       T const &a0) noexcept
  Requires(std::tuple<T, T>, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto t = trunc(a0); 
      return std::make_tuple(a0 - t, t); 
    }
    else
      return std::make_tuple(Zero(as(a0)), a0);
  }
}

#endif
