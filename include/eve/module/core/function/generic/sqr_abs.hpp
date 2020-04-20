//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SQR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SQR_ABS_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/sqr.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sqr_abs_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return sqr(a);
  }
}

#endif
