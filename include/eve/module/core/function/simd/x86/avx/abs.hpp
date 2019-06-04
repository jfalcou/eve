//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N,avx_> abs_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v) noexcept
  {
    if constexpr(std::is_integral_v<T>)
    {
      if constexpr( std::is_signed_v<T> )
      {
        return aggregate(eve::abs, v);
      }
      else
      {
        return v;
      }
    }
    else
    {
      return bitwise_notand(Mzero(as(v)),v);
    }
  }
}

#endif
