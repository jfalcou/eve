//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/two_prod.hpp>
#include <eve/module/core/regular/two_add.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE kumi::tuple<T, T, T>
  three_fma_(EVE_SUPPORTS(cpu_)
           , const T& a
           , const T& b
           , const T& c) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto x =  numeric(fma)(a, b, c);
      auto [u1, u2] = two_prod(a, b);
      auto [a1, z2] = two_add(b, u2);
      auto [b1, b2] = two_add(u1, a1);
      return {x, (b1-x)+b2};
    }
    else return apply_over3(three_fma, a, b, c);
  }
}
