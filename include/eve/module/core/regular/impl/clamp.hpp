//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto clamp_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b
                                  , V const &c) noexcept
  requires compatible_values<T,U> && compatible_values<T,V>
  {
    return arithmetic_call(clamp, a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE auto clamp_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return eve::min(eve::max(a, b), c);
  }
}

