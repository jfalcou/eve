//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACSC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACSC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/asin.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acsc_(EVE_SUPPORTS(cpu_)
                                      , T const &a0) noexcept
  {
    if constexpr(native<T>)  return eve::asin(rec(a0));
    else                     return apply_over(acsc, a0);
  }

}

#endif
