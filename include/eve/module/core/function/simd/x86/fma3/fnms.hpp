//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_FMA3_FNMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_FMA3_FNMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/fms.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> fnms_(EVE_SUPPORTS(avx_), wide<T, N, sse_> const &a,
                                         wide<T, N, sse_> const &b,
                                         wide<T, N, sse_> const &c
                                        ) noexcept
  {
    return fms(-a,b,c);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> fnms_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a,
                                         wide<T, N, avx_> const &b,
                                         wide<T, N, avx_> const &c
                                        ) noexcept
  {
    return fms(-a,b,c);
  }
}

#endif
