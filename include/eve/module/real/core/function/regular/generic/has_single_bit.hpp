//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/popcount.hpp>
#include <eve/constant/one.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<integral_real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> has_single_bit_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return T(popcount(a)) == one(as(a));
    }
    else
      return apply_over(has_single_bit, a);
  }
}
