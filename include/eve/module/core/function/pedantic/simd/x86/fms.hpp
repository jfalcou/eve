//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fms_(EVE_SUPPORTS(avx2_),
                                       pedantic_type const &,
                                       wide<T, N, ABI> const &a,
                                       wide<T, N, ABI> const &b,
                                       wide<T, N, ABI> const &c) noexcept
  {
    if constexpr( supports_fma3 || supports_fma4  )
    {
      return fms(a, b, c);
    }
    else
    {
      return fms_(EVE_RETARGET(cpu_), pedantic_type(), a, b, c);
    }
  }
}
