//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_INF_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_INF_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_inf_(EVE_SUPPORTS(cpu_)
                                                   , T a) noexcept
  {
    if constexpr(std::is_integral_v<T>)
      return True<T>();
    else
      return abs(a) != Inf<T>(); 
  }

}

#endif
