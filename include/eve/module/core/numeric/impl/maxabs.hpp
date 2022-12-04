//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/numeric/max.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_),
        numeric_type const&,
        T const& a,
        U const& b) noexcept
-> decltype(maxabs(a, b))
{
  return arithmetic_call(numeric(maxabs), a, b);
}

template<value T>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  return eve::numeric(max)(eve::abs(a), eve::abs(b));
}
}
