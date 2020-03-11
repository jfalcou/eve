//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_REFINE_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_REFINE_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE T refine_rec_(EVE_SUPPORTS(cpu_), T const &a0, T const &x) noexcept
  {
    // Newton-Raphson: 1/X ~= (1-a0*x)*x + x
    return fma(fnma(x, a0, One(as(a0))), x, x);
  }
}

#endif
