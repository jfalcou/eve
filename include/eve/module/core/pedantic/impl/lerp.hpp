//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/pedantic/fma.hpp>
#include <eve/module/core/pedantic/fnma.hpp>
#include <eve/module/core/regular/all.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U, floating_real_value V>
EVE_FORCEINLINE auto
lerp_(EVE_SUPPORTS(cpu_),
      pedantic_type const&,
      T const& a,
      U const& b,
      V const& t) noexcept requires compatible_values<T, U> && compatible_values<T, V>
{
  return arithmetic_call(pedantic(lerp), a, b, t);
}

template<floating_real_value T>
EVE_FORCEINLINE T
lerp_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a, T const& b, T const& t) noexcept
{
  return pedantic(fma)(t, b, pedantic(fnma)(t, a, a));
}
}
