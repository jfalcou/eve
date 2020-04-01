//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CEIL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CEIL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/trunc.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<real_value T>
  EVE_FORCEINLINE constexpr auto ceil_(EVE_SUPPORTS(cpu_)
                                      , T const &a0) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto z = trunc(a0);
      return inc[ z < a0 ](z);
    }
    else
      return a0;
  }
}

#endif
