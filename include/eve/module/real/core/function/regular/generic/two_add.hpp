//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <array>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE std::array<T, 2>
  two_add_(EVE_SUPPORTS(cpu_)
          , const T& a
          , const T& b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      T r0 = a + b;
      T z = r0 - a;
      T r1 = a-(r0-z)+(b-z);
      if constexpr(eve::platform::supports_infinites)
        r1 = if_else(is_infinite(r0), eve::zero, r1);
      return {r0, r1};
    }
    else return apply_over2(two_add, a, b);
  }
}
