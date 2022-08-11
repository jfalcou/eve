//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/saturated/abs.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
maxmag_(EVE_SUPPORTS(cpu_),
        saturated_type const&,
        T const& a,
        U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(saturated(maxmag), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
maxmag_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a, T const& b) noexcept
{
  auto aa = saturated(eve::abs)(a);
  auto bb = saturated(eve::abs)(b);
  if constexpr( simd_value<T> )
  {
    auto tmp = if_else(is_not_greater_equal(aa, bb), b, eve::max(a, b));
    return if_else(is_not_greater_equal(bb, aa), a, tmp);
  }
  else { return aa < bb ? b : bb < aa ? a : saturated(eve::max)(a, b); }
}
}
