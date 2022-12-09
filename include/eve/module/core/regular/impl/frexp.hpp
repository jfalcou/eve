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
#include <eve/detail/kumi.hpp>
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/regular/ifrexp.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// tagged cases
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
frexp_(EVE_SUPPORTS(cpu_), raw_type const&, T const& a0) noexcept
{
  auto [m, e] = raw(ifrexp)(a0);
  return kumi::make_tuple(m, to_<T>(e));
}

// -----------------------------------------------------------------------------------------------
// Regular case
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
frexp_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  auto [m, e] = ifrexp(a0);
  return kumi::make_tuple(m, to_<T>(e));
}
}
