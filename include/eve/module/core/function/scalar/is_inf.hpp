//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_INF_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_INF_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_inf_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>) { return eve::abs(a) == Inf<T>(); }
    else
    {
      return false;
    }
  }
}

#endif
