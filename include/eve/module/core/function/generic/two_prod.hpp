//==================================================================================================
/**v
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/platform.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/two_split.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>
#include <eve/detail/apply_over.hpp>
#include <tuple>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto two_prod_(EVE_SUPPORTS(cpu_)
                                 , const T& a
                                 , const T& b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto [a1, a2] = two_split(a);
      auto [b1, b2] = two_split(b);
      T r0 = a*b;
      T r1 = a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2);
      if constexpr(eve::platform::supports_invalids)
        r1 = if_else(is_not_finite(r0), eve::zero, r1);
      return std::make_tuple(r0, r1);
    }
    else return apply_over2(two_prod, a, b);
  }
}

