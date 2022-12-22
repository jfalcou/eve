//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/pedantic/min.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/arch/platform.hpp>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_),
        pedantic_type const&,
        T const& a,
        U const& b) noexcept
-> decltype(minabs(a, b))
{
  return arithmetic_call(pedantic(minabs), a, b);
}

template<value T>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a, T const& b) noexcept
{
  return pedantic(min)(eve::abs(a), eve::abs(b));
}

//================================================================================================
// N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
minabs_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(minabs(a0, a1, args...))
{
  using r_t = decltype(minabs(a0, a1, args...));
  r_t that(pedantic(minabs)(r_t(a0), r_t(a1)));
  ((that = pedantic(minabs)(that, r_t(args))), ...);
  return that;
}
}
