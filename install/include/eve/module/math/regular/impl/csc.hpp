//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/sin.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE auto csc_(EVE_SUPPORTS(cpu_), D const &, T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return rec(D()(sin)(a0));
    else
      return apply_over(D()(csc), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto csc_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return rec(sin(a0));
    else
      return apply_over(csc, a0);
  }
}
