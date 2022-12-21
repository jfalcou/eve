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
#include <eve/module/core/pedantic/max.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/saturated/abs.hpp>
#include <eve/arch/platform.hpp>

#include <type_traits>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_),
        pedantic_type const&,
        T const& a,
        U const& b) noexcept
-> decltype(maxabs(a, b))
{
  return arithmetic_call(pedantic(maxabs), a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a, T const& b) noexcept
{
  return pedantic(max)(eve::abs(a), eve::abs(b));
}
}
