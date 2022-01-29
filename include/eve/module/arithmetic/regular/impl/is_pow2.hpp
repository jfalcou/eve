//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/is_gtz.hpp>
#include <eve/module/arithmetic/regular/is_eqz.hpp>
#include <eve/module/arithmetic/regular/dec.hpp>
#include <eve/module/arithmetic/regular/is_eqz.hpp>

namespace eve::detail
{
  template<integral_real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_pow2_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return is_gtz(a) && is_eqz(a & dec(a));
    }
    else
      return apply_over(is_pow2, a);
  }
}
