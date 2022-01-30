//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> fma_(EVE_SUPPORTS(avx2_),
                                        pedantic_type const &,
                                        wide<T, N> const &a,
                                        wide<T, N> const &b,
                                        wide<T, N> const &c) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    if constexpr( supports_fma3 )
    {
      return fma(a, b, c);
    }
    else
    {
      return fma_(EVE_RETARGET(cpu_), pedantic_type(), a, b, c);
    }
  }
}
