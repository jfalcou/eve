//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SQR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SQR_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/sqr.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sqr_abs_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  requires(T, behave_as<floating_point,T>)
  {
    return sqr(a);
  }
}

#endif
