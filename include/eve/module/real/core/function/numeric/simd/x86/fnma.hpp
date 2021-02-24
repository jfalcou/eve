//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/numeric.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fnma_(EVE_SUPPORTS(avx2_),
                                        numeric_type const &,
                                        wide<T, N, ABI> const &a,
                                        wide<T, N, ABI> const &b,
                                        wide<T, N, ABI> const &c) noexcept
  {
    if constexpr( supports_fma3 || supports_fma4  )
    {
      return fnma(a, b, c);
    }
    else
    {
      return fnma_(EVE_RETARGET(cpu_), numeric_type(), a, b, c);
    }
  }
}
