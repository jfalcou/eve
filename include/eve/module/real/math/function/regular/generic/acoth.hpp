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
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/atanh.hpp>
#include <eve/function/rec.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acoth_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return eve::atanh(rec(x));
    }
    else
    {
      return apply_over(acoth, x);
    }
  }
}

