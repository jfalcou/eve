//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_LOG10_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_LOG10_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation for avx
  template<typename T, typename N>
  EVE_FORCEINLINE auto log10_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v) noexcept
  requires(wide<T, N, avx_>, floating_point<T>)
  {
    if constexpr(current_api < avx2)
    {
      return plain_(log10)(v);
    }
    else
    {
      return musl_(log10)(v);
    }
  }
}

#endif
