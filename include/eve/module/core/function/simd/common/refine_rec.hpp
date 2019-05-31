//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REFINE_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REFINE_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> refine_rec_ ( EVE_SUPPORTS(cpu_),
                                                wide<T, N, ABI> const &a0,
                                                wide<T, N, ABI> const &x
                                              ) noexcept
  {
    // Newton-Raphson: 1/X ~= (1-a0*x)*x + x
    return fma(fnma(x, a0, One(as(a0))), x, x);
  }
}

#endif
