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
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
minmag_(EVE_SUPPORTS(cpu_),
        numeric_type const&,
        T const& a,
        U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(numeric(minmag), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
minmag_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  auto aa = if_else(is_nan(a), b, a);
  auto bb = if_else(is_nan(b), a, b);
  return eve::pedantic(minmag)(aa, bb);
}
}
