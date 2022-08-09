//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
dist_(EVE_SUPPORTS(cpu_),
      saturated_type const&,
      T const& a,
      U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(saturated(dist), a, b);
}

template<real_value T>
EVE_FORCEINLINE T
dist_(EVE_SUPPORTS(cpu_),
      saturated_type const&,
      T const& a,
      T const& b) noexcept requires has_native_abi_v<T>
{
  auto d = dist(a, b);
  if constexpr( signed_integral_value<T> ) return if_else(is_ltz(d), valmax(eve::as(a)), d);
  else return d;
}
}
