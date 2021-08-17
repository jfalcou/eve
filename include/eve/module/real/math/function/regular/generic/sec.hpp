//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/rec.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto sec_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return rec(D()(eve::cos)(a0));
    }
    else
    {
      return apply_over(D()(sec), a0);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sec_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return rec(eve::cos(a0));
    }
    else
    {
      return apply_over(sec, a0);
    }
  }

}

